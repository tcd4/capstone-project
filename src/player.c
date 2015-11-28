#include "player.h"
#include "level.h"


vec2_t	gravity;


static uint8	_player_flags = 0;
static vec2_t	_spawn;
static vec2_t	_jump_speed;
static vec2_t	_move_speed;
static vec2_t	_attack_box_offset;


void player_think( Entity *self );
void player_touch( dataptr d1, dataptr d2, double *moved );
void player_die( Entity *self );
void player_free( Entity *self );

void player_jump( dataptr d );
void player_move_right( dataptr d );
void player_move_left( dataptr d );
void player_stop( dataptr d );
void player_attack( dataptr d );

void player_attack_done( Entity *self );
void player_die_done( Entity *self );

void turn_off_player_cmds();
void turn_on_player_cmds();

void create_attack_box( Entity *owner, Dict *config );
void update_attack_box( Entity *owner, Entity *self );


Entity* create_player( char *file )
{
  Entity *new;
  Dict *config;
  vec2_t size, pos, offset;
  char name[ 6 ] = "player";
  
  config = Parse( file );
  if( !config )
  {
    Log( ERROR, "couldn't load player config %s", file );
    return NULL;
  }
  
  new = create_entity();
  if( !new )
  {
    Log( ERROR, "couldn't make player entity" );
    return NULL;
  }
  
  new->name = ( char* ) malloc( sizeof( char ) * 6 );
  strncpy( new->name, name, 6 );
  new->ent_type = ENT_PLAYER;
  
  new->visible = 1;
  new->draw_state = PLAYER_IDLE;
  add_draw_state( new, Find_In_Dict( config, "idle" ), NULL );
  add_draw_state( new, Find_In_Dict( config, "walk" ), NULL );
  add_draw_state( new, Find_In_Dict( config, "jump" ), NULL );
  add_draw_state( new, Find_In_Dict( config, "attack" ), player_attack_done );
  add_draw_state( new, Find_In_Dict( config, "die" ), player_die_done );
  
  Str_As_Vec2( Find_In_Dict( config, "scale" ), new->scale );
  Str_As_Vec2( Find_In_Dict( config, "rotation" ), new->rotation );
  
  Str_As_Vec2( Find_In_Dict( config, "gravity" ), gravity );
  Str_As_Vec2( Find_In_Dict( config, "spawn" ), _spawn );
  Str_As_Vec2( Find_In_Dict( config, "size" ), size );
  Str_As_Vec2( Find_In_Dict( config, "offset" ), offset );
  Str_As_Vec2( Find_In_Dict( config, "jump_speed" ), _jump_speed );
  Str_As_Vec2( Find_In_Dict( config, "move_speed" ), _move_speed );
  
  Vec2_Copy( _spawn, pos );
  Vec2_Add( pos, offset, pos );
  
  new->body = create_body( new, PLAYER_GROUP, size, pos, player_touch );
  add_ent_to_space( new );
  
  Vec2_Copy( _spawn, new->position );
  Vec2_Copy( offset, new->offset );
  Vec2_Copy( gravity, new->body->acceleration );
  _player_flags |= PLAYER_GROUNDED;

  Str_As_UInt( Find_In_Dict( config, "think_rate" ), &new->think_rate );

  new->Think = player_think;
  new->Die = player_die;
  new->Free = player_free;
  
  if( !add_cmd( TRUE, "player_move_right", SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_DPAD_RIGHT, 0, player_move_right, new ) )
    Log( ERROR, "failed to add player_move_right cmd" );

  if( !add_cmd( TRUE, "player_move_left", SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_DPAD_LEFT, 0, player_move_left, new ) )
    Log( ERROR, "failed to add player_move_left cmd" );
  
  if( !add_cmd( TRUE, "player_jump", SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_A, 0, player_jump, new ) )
    Log( ERROR, "failed to add player_jump cmd" );
  
  if( !add_cmd( TRUE, "player_attack", SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_X, 0, player_attack, new ) )
    Log( ERROR, "failed to add player_attack cmd" );
  
  if( !add_cmd( TRUE, "player_stop_right", SDL_CONTROLLERBUTTONUP, SDL_CONTROLLER_BUTTON_DPAD_RIGHT, 0, player_stop, new ) )
    Log( ERROR, "failed to add player_stop_right cmd" );
  
  if( !add_cmd( TRUE, "player_stop_left", SDL_CONTROLLERBUTTONUP, SDL_CONTROLLER_BUTTON_DPAD_LEFT, 0, player_stop, new ) )
    Log( ERROR, "failed to add player_stop_left cmd" );
  
  create_attack_box( new, config );
  
  return new;
}


void create_attack_box( Entity *owner, Dict *config )
{
  Entity *new;
  char name[ 17 ] = "player_attack_box";
  vec2_t size;
  
  new = create_entity();
  if( !new )
  {
    Log( ERROR, "couldn't make player attack entity" );
    return;
  }
  
  new->name = ( char* ) malloc( sizeof( char ) * 17 );
  strncpy( new->name, name, 17 );
  new->ent_type = ENT_ATTACK_BOX;
  new->visible = 0;
  
  Str_As_Vec2( Find_In_Dict( config, "attack_box_offset" ), _attack_box_offset );
  Str_As_Vec2( Find_In_Dict( config, "attack_box_size" ), size );
  new->body = create_body( new, PLAYER_GROUP, size, owner->body->position, NULL );
  
  owner->slaves = new;
  new->owner = owner;
}


void player_think( Entity *self )
{
  if( ( self->ent_type != ENT_PLAYER ) || ( self->think_state & STATE_DEAD ) )
    return;
  
  /* update attack box when attacking */
  if( self->draw_state == PLAYER_ATTACK )
    update_attack_box( self, self->slaves );
}


void update_attack_box( Entity *owner, Entity *self )
{
  Vec2_Copy( owner->body->position, self->body->position );
  Vec2_Add( self->body->position, _attack_box_offset, self->body->position );
}


void player_touch( dataptr d1, dataptr d2, double *moved )
{
  Entity *self, *other;
  vec2_t tmp;
  
  self = ( Entity* )( d1 );
  other = ( Entity* )( d2 );
  
  if( other->ent_type == ENT_WORLD )
  {
    if( _player_flags & PLAYER_GROUNDED )
    {
      Vec2_Set( tmp, 0, moved[ YA ] );
      Vec2_Subtract( self->body->position, tmp, self->body->position );
    }
    else
    {
      /* move back along the y-axis */
      tmp[ YA ] = self->body->position[ YA ] - moved[ YA ];
   
      /* collide below */
      if( tmp[ YA ] >= other->body->position[ YA ] + other->body->size[ YA ] )
      {
	self->body->position[ YA ] = other->body->position[ YA ] + other->body->size[ YA ] + 5;
	self->body->velocity[ YA ] = 0;
	return;
      }
      
      /* move back along the x-axis */
      tmp[ XA ] = self->body->position[ XA ] - moved[ XA ];
      
      /* collide left */
      if( tmp[ XA ] <= other->body->position[ XA ] )
      {
	self->body->position[ XA ] = other->body->position[ XA ] - self->body->size[ XA ];
	return;
      }
      
      /* collide right */
      if( tmp[ XA ] >= other->body->position[ XA ] + other->body->size[ XA ] )
      {
	self->body->position[ XA ] = other->body->position[ XA ] + other->body->size[ XA ] + 5;
	return;
      }
      
      /* collision on top */   
      /* ground the player */
      _player_flags |= PLAYER_GROUNDED;

      /* set animation state */      
      if( self->body->velocity[ XA ] )
      {
	reset_actor( self->actors[ PLAYER_WALK ] );
	self->draw_state = PLAYER_WALK;
      }
      else if( self->draw_state == PLAYER_JUMP )
	self->draw_state = PLAYER_IDLE;
    }
  }
  else if( other->ent_type == ENT_ENEMY )
  {
    self->Die( self );
  }
  else if( other->ent_type == ENT_ATTACK_BOX && other->owner != self )
  {
    self->Die( self );
  }
}


void player_die( Entity *self )
{
  self->think_state |= STATE_DEAD;
  turn_off_player_cmds();
  remove_ent_from_space( self );
}


void player_free( Entity *self )
{
  remove_cmd_by_name( "player_move_right" );
  remove_cmd_by_name( "player_move_left" );
  remove_cmd_by_name( "player_jump" );
  remove_cmd_by_name( "player_attack" );
  remove_cmd_by_name( "player_stop_right" );
  remove_cmd_by_name( "player_stop_left" );
}


void player_jump( dataptr d )
{
  Entity *self;
  
  self = ( Entity* )( d );
  
  if( self->draw_state == PLAYER_JUMP )
    return;

  _player_flags &= ~PLAYER_GROUNDED;
  self->draw_state = PLAYER_JUMP;
  
  self->body->velocity[ YA ] = -_jump_speed[ YA ];
  self->body->position[ YA ] -= 5;
}


void player_move_right( dataptr d )
{
  Entity *self;
  
  self = ( Entity* )( d );

  if( self->draw_state == PLAYER_JUMP || self->draw_state == PLAYER_ATTACK )
    return;
  
  self->body->velocity[ XA ] = _move_speed[ XA ];
  Vec2_Set( self->scale, -1, 1 );
  
  self->draw_state = PLAYER_WALK;
}


void player_move_left( dataptr d )
{
  Entity *self;
  
  self = ( Entity* )( d );

  if( self->draw_state == PLAYER_JUMP || self->draw_state == PLAYER_ATTACK )
    return;
  
  self->body->velocity[ XA ] = -_move_speed[ XA ];
  Vec2_Set( self->scale, 1, 1 );
  
  self->draw_state = PLAYER_WALK;
}


void player_stop( dataptr d )
{
  Entity *self;
  
  self = ( Entity* )( d );
  
  reset_actor( self->actors[ PLAYER_WALK ] );
  
  self->body->velocity[ XA ] = 0;
  
  if( self->draw_state == PLAYER_WALK )
    self->draw_state = PLAYER_IDLE;
}


void player_attack( dataptr d )
{
  Entity *self;
  
  self = ( Entity* )( d );
  
  if( self->draw_state == PLAYER_ATTACK )
    return;
  
  turn_off_cmd( "player_move_right" );
  turn_off_cmd( "player_move_left" );
  turn_off_cmd( "player_jump" );
  turn_off_cmd( "player_attack" );
  
  update_attack_box( self, self->slaves );
  self->draw_state = PLAYER_ATTACK;
  
  if( _player_flags & PLAYER_GROUNDED )
    Vec2_Set( self->body->velocity, 0, 0 );
}


void player_attack_done( Entity *self )
{
  self->draw_state = PLAYER_IDLE;
  if( _player_flags & PLAYER_GROUNDED )
    self->draw_state = PLAYER_IDLE;
  else
    self->draw_state = PLAYER_JUMP;
  
  reset_actor( self->actors[ PLAYER_ATTACK ] );
  turn_on_player_cmds();
}


void player_die_done( Entity *self )
{
  self->visible = 0;
  reset_actor( self->actors[ PLAYER_DIE ] );
  self->draw_state = PLAYER_IDLE;
}


void turn_off_player_cmds()
{
  turn_off_cmd( "player_move_right" );
  turn_off_cmd( "player_move_left" );
  turn_off_cmd( "player_jump" );
  turn_off_cmd( "player_attack" );
  turn_off_cmd( "player_stop_right" );
  turn_off_cmd( "player_stop_left" );
}


void turn_on_player_cmds()
{
  turn_on_cmd( "player_move_right" );
  turn_on_cmd( "player_move_left" );
  turn_on_cmd( "player_jump" );
  turn_on_cmd( "player_attack" );
  turn_on_cmd( "player_stop_right" );
  turn_on_cmd( "player_stop_left" );
}


/* eof */