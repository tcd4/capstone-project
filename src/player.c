#include "player.h"
#include "level.h"


vec2_t	gravity;


static uint8	_player_flags = 0;
static vec2_t	_spawn;


void player_think( Entity *self );
void player_touch( dataptr d1, dataptr d2, double *moved );
void player_die( Entity *self );
void player_free( Entity *self );

void player_jump( dataptr d );
void player_move_right( dataptr d );
void player_move_left( dataptr d );
void player_attack( dataptr d );

void player_attack_done( Entity *self );
void player_die_done( Entity *self );


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
  add_draw_state( new, Find_In_Dict( config, "attack" ), player_attack_done );
  add_draw_state( new, Find_In_Dict( config, "die" ), player_die_done );
  
  Str_As_Vec2( Find_In_Dict( config, "scale" ), new->scale );
  Str_As_Vec2( Find_In_Dict( config, "rotation" ), new->rotation );
  
  Str_As_Vec2( Find_In_Dict( config, "gravity" ), gravity );
  Str_As_Vec2( Find_In_Dict( config, "spawn" ), _spawn );
  Str_As_Vec2( Find_In_Dict( config, "size" ), size );
  Str_As_Vec2( Find_In_Dict( config, "offset" ), offset );
  
  Vec2_Copy( _spawn, pos );
  Vec2_Add( pos, offset, pos );
  
  new->body = create_body( new, PLAYER_GROUP, size, pos, player_touch );
  add_ent_to_space( new );
  
  Vec2_Copy( _spawn, new->position );
  Vec2_Copy( offset, new->offset );
  Vec2_Copy( gravity, new->body->acceleration );
  
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
  
  return new;
}


void player_think( Entity *self )
{
  if( ( self->ent_type != ENT_PLAYER ) || ( self->think_state & STATE_DEAD ) )
    return;
}


void player_touch( dataptr d1, dataptr d2, double *moved )
{
  Entity *self, *other;
  
  self = ( Entity* )( d1 );
  other = ( Entity* )( d2 );
  
  Vec2_Subtract( self->body->position, moved, self->body->position );
  
  if( other->ent_type == ENT_WORLD )
    return;
}


void player_die( Entity *self )
{
}


void player_free( Entity *self )
{
}


void player_jump( dataptr d )
{
}


void player_move_right( dataptr d )
{
}


void player_move_left( dataptr d )
{
}


void player_attack( dataptr d )
{
}


void player_attack_done( Entity *self )
{
}


void player_die_done( Entity *self )
{
}


/* eof */