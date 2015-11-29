#include "enemy.h"
#include "level.h"


#define EAB_ADDED 1

enum
{
  ENEMY_SEARCHING = 0,
  ENEMY_CHARGING,
  ENEMY_ATTACKING
};

extern vec2_t	gravity;

static vec2_t	_move_speed;
static vec2_t	_attack_box_offset;
static uint8	_ab_added = 0;


void enemy_think( Entity *self );
void enemy_touch( dataptr d1, dataptr d2, double *moved );
void enemy_die( Entity *self );

void enemy_attack_done( Entity *self );
void enemy_die_done( Entity *self );

void create_eattack_box( Entity *owner, Dict *config );
void update_eattack_box( Entity *owner, Entity *self );
void eattack_box_think( Entity *self );


void create_enemy( char *file, vec2_t spawn )
{
  Entity *new;
  Dict *config;
  vec2_t size, offset;
  char name[ 5 ] = "enemy";
  
  config = Parse( file );
  if( !config )
  {
    Log( ERROR, "couldn't load enemy config %s", file );
    return;
  }
  
  new = create_entity();
  if( !new )
  {
    Log( ERROR, "couldn't make enemy entity" );
    return;
  }
  
  new->name = ( char* ) malloc( sizeof( char ) * 5 );
  strncpy( new->name, name, 5 );
  new->ent_type = ENT_ENEMY;
  
  new->visible = 1;
  new->draw_state = ENEMY_IDLE;
  add_draw_state( new, Find_In_Dict( config, "idle" ), NULL );
  add_draw_state( new, Find_In_Dict( config, "walk" ), NULL );
  add_draw_state( new, Find_In_Dict( config, "attack" ), enemy_attack_done );
  add_draw_state( new, Find_In_Dict( config, "die" ), enemy_die_done );
  
  Str_As_Vec2( Find_In_Dict( config, "scale" ), new->scale );
  Str_As_Vec2( Find_In_Dict( config, "rotation" ), new->rotation );
  Str_As_Vec2( Find_In_Dict( config, "size" ), size );
  Str_As_Vec2( Find_In_Dict( config, "offset" ), offset );
  Str_As_Vec2( Find_In_Dict( config, "move_speed" ), _move_speed );
  Str_As_UInt( Find_In_Dict( config, "think_rate" ), &new->think_rate );
  
  new->body = create_body( new, 3, size, spawn, enemy_touch );
  add_ent_to_space( new );
  
  Vec2_Add( spawn, offset, spawn );
  Vec2_Copy( offset, new->offset );
  Vec2_Copy( gravity, new->body->acceleration );
  
  create_eattack_box( new, config );
  
  new->think_state = 1;
  new->flags |= ENEMY_SEARCHING;
  
  new->Think = enemy_think;
  new->Die = enemy_die;
}


void create_eattack_box( Entity *owner, Dict *config )
{
  Entity *new;
  char name[ 16 ] = "enemy_attack_box";
  vec2_t size;
  
  new = create_entity();
  if( !new )
  {
    Log( ERROR, "couldn't make enemy attack entity" );
    return;
  }
  
  new->name = ( char* ) malloc( sizeof( char ) * 16 );
  strncpy( new->name, name, 16 );
  new->ent_type = ENT_ATTACK_BOX;
  new->visible = 0;
  
  Str_As_Vec2( Find_In_Dict( config, "attack_box_offset" ), _attack_box_offset );
  Str_As_Vec2( Find_In_Dict( config, "attack_box_size" ), size );
  new->body = create_body( new, 3, size, owner->body->position, NULL );
  
  new->think_rate = 1;
  new->think_state |= STATE_DUMB;
  new->Think = eattack_box_think;
  
  owner->slaves = new;
  new->owner = owner;
}


void enemy_think( Entity *self )
{
  Entity *player;
  vec2_t distance_between_l, distance_between_r;
  
  if( ( self->ent_type != ENT_ENEMY ) || ( self->think_state & STATE_DEAD ) )
    return;
  
  player = get_player();
  if( player->think_state == STATE_DEAD )
  {
    self->body->velocity[ XA ] = 0;
    return;
  }
  
  Vec2_Set( distance_between_l, self->body->position[ XA ] - ( player->body->position[ XA ] + player->body->size[ XA ] ), self->body->position[ YA ] - player->body->position[ YA ]  );
  Vec2_Set( distance_between_r, self->body->position[ XA ] + self->body->size[ XA ] - player->body->position[ XA ], self->body->position[ YA ] );
  
  switch( self->flags )
  {
    case ENEMY_SEARCHING:
      self->draw_state = ENEMY_IDLE;
      self->body->velocity[ XA ] = 0;
      
      if( ( ( distance_between_l[ YA ] >= ARGO_HEIGHT ) || ( distance_between_l[ YA ] <= -ARGO_HEIGHT ) ) || \
	( ( distance_between_l[ XA ] >= ARGO_DISTANCE ) || ( distance_between_r[ XA ] <= -ARGO_DISTANCE ) ) )
	return;
      
      if( distance_between_l[ XA ] < 0 )
	self->scale[ XA ] = -1;
      else
	self->scale[ XA ] = 1;
      
      self->flags = ENEMY_CHARGING;
      break;
      
    case ENEMY_CHARGING:      
      self->draw_state = ENEMY_WALK;
      
      if( ( ( distance_between_l[ YA ] >= ARGO_HEIGHT ) || ( distance_between_l[ YA ] <= -ARGO_HEIGHT ) ) || \
	( ( distance_between_l[ XA ] >= ARGO_DISTANCE ) || ( distance_between_r[ XA ] <= -ARGO_DISTANCE ) ) )
      {
	self->flags = ENEMY_SEARCHING;
	reset_actor( self->actors[ ENEMY_WALK ] );
      }
      
      if( ( ( distance_between_l[ XA ] <= ATTACK_DISTANCE ) && ( distance_between_l[ XA ] > 0 ) ) || \
	( ( distance_between_r[ XA ] >= -ATTACK_DISTANCE ) && ( distance_between_r[ XA ] < 0 ) ) )
      {
	self->flags = ENEMY_ATTACKING;
	reset_actor( self->actors[ ENEMY_WALK ] );
	return;
      }
      
      if( distance_between_l[ XA ] < 0 )
	self->body->velocity[ XA ] = _move_speed[ XA ];
      else
	self->body->velocity[ XA ] = -_move_speed[ XA ];
           
      break;
      
    case ENEMY_ATTACKING:     
      self->draw_state = ENEMY_ATTACK;
      self->slaves->think_state &= ~STATE_DUMB;
      self->body->velocity[ XA ] = 0; 
      
      if( ( ( distance_between_l[ YA ] >= ARGO_HEIGHT ) || ( distance_between_l[ YA ] <= -ARGO_HEIGHT ) ) || \
	( ( distance_between_l[ XA ] >= ARGO_DISTANCE ) || ( distance_between_r[ XA ] <= -ARGO_DISTANCE ) ) )
      {
	self->flags = ENEMY_SEARCHING;
	reset_actor( self->actors[ ENEMY_WALK ] );
      }
      
      break;
  }
}


void eattack_box_think( Entity *self )
{
  if( self->think_state & STATE_DUMB )
    return;    
  
  if( !( _ab_added & EAB_ADDED ) && self->owner->actors[ ENEMY_ATTACK ]->frame >= 10 )
  {
    add_ent_to_space( self );
    _ab_added = EAB_ADDED;
  }
  update_eattack_box( self->owner, self );
}


void update_eattack_box( Entity *owner, Entity *self )
{  
  if( owner->scale[ XA ] < 0 )
    self->body->position[ XA ] = owner->body->position[ XA ] + owner->body->size[ XA ] + _attack_box_offset[ XA ];
  else
    self->body->position[ XA ] = owner->body->position[ XA ] - _attack_box_offset[ XA ] - self->body->size[ XA ];
  
  self->body->position[ YA ] = owner->body->position[ YA ] + _attack_box_offset[ YA ];
}


void enemy_touch( dataptr d1, dataptr d2, double *moved )
{
  Entity *self, *other;
  vec2_t tmp;
  
  self = ( Entity* )( d1 );
  other = ( Entity* )( d2 );
  
  if( other->ent_type == ENT_WORLD )
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
    self->body->position[ YA ] = tmp[ YA ];
    self->body->velocity[ YA ] = 0;
  }
  else if( other->ent_type == ENT_PLAYER )
  {
    self->Die( self );
  }
  else if( other->ent_type == ENT_ATTACK_BOX && other->owner != self )
  {
    self->Die( self );
  }
}


void enemy_die( Entity *self )
{
  if( self->draw_state == ENEMY_ATTACK )
    enemy_attack_done( self );
  
  self->draw_state = ENEMY_DIE;
  self->think_state |= STATE_DEAD;
  remove_ent_from_space( self );
}


void enemy_attack_done( Entity *self )
{
  reset_actor( self->actors[ ENEMY_ATTACK ] );
  self->flags = ENEMY_SEARCHING;
  
  self->slaves->think_state |= STATE_DUMB;
  remove_ent_from_space( self->slaves );
  _ab_added &= ~EAB_ADDED;
  
  if( get_player()->think_state == STATE_DEAD )
    self->draw_state = ENEMY_IDLE;
}


void enemy_die_done( Entity *self )
{
  self->visible = 0;
  reset_actor( self->actors[ ENEMY_DIE ] );
  self->draw_state = ENEMY_IDLE;
}

















/* eof */