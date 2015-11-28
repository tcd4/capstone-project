#include "enemy.h"
#include "level.h"


extern vec2_t	gravity;

static vec2_t	_move_speed;
static vec2_t	_attack_box_offset;


void enemy_think( Entity *self );
void enemy_touch( dataptr d1, dataptr d2, double *moved );
void enemy_die( Entity *self );

void enemy_attack_done( Entity *self );
void enemy_die_done( Entity *self );

void create_eattack_box( Entity *owner, Dict *config );
void update_eattack_box( Entity *owner, Entity *self );


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
  add_draw_state( new, Find_In_Dict( config, "jump" ), NULL );
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
  
  new->Think = enemy_think;
  new->Die = enemy_die;
}


void create_eattack_box( Entity *owner, Dict *config )
{
}


void enemy_think( Entity *self )
{
  if( ( self->ent_type != ENT_PLAYER ) || ( self->think_state & STATE_DEAD ) )
    return;
}


void update_eattack_box( Entity *owner, Entity *self )
{
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
    
    /* set animation state */      
    if( self->body->velocity[ XA ] )
    {
      reset_actor( self->actors[ ENEMY_WALK ] );
      self->draw_state = ENEMY_WALK;
    }
    else
      self->draw_state = ENEMY_IDLE;
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
}


void enemy_die_done( Entity *self )
{
  self->visible = 0;
  reset_actor( self->actors[ ENEMY_DIE ] );
  self->draw_state = ENEMY_IDLE;
}

















/* eof */