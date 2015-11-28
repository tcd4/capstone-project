#include "entity.h"


static Entity	_ent_list[ MAX_ENTITIES ];
static uint32	_num_ents = 0;
static Space	*_ent_space = NULL;


void init_entity_system()
{
  Log( INFO, "Initializing Entity System" );
  
  memset( _ent_list, 0, sizeof( Entity ) * MAX_ENTITIES );
  
  _ent_space = create_space( PHYSICS_STEPS );
  if( !_ent_space )
  {
    Log( FATAL, "No space to play games." );
    exit ( -1 );
  }
  
  Log( INFO, "Entity System Initialized" );
}


void close_entity_system()
{
  Log( INFO, "Closing Entity System" );
  free_all_entities();
  Log( INFO, "Entity System Closed" );
  
  Log( INFO, "Destroying Space" );
  free_space( &_ent_space );
  Log( INFO, "Space Destroyed" );
}


Entity* create_entity()
{
  int i, e;

  if( _num_ents + 1 >= MAX_ENTITIES )
  {
    Log( WARN, "Entity list is full. No more entities can be made." );
    return NULL;
  }

  e = 0;
  for( i = 0; i < MAX_ENTITIES && e <= _num_ents; i++ )
  {
    if( !_ent_list[ i ].inuse )
    {
      _ent_list[ i ].inuse = 1;
      _num_ents++;
      _ent_list[ i ].self = &_ent_list[ i ];
      
      return &_ent_list[ i ];
    }
    
    e++;
  }

  Log( WARN, "New entity was not created." );
  return NULL;
}


void free_entity( Entity *ent )
{
  int i;
  
  _num_ents--;
  ent->inuse = 0;

  for( i = 0; i < MAX_ACTORS; i++ )
  {
    if( ent->actors[ i ] )
      free_actor( &ent->actors[ i ] );
  }
  
  if( ent->name )
    free( ent->name );
  
  if( ent->body )
    free_body( _ent_space, &ent->body );
  
  if( ent->Free )
    ent->Free( ent );  

  memset( ent, 0, sizeof( Entity ) );
}


void free_all_entities()
{
  int i;

  for( i = 0; i < MAX_ENTITIES && _num_ents > 0; i++ )
  {
    free_entity( &_ent_list[ i ] );
  }
}


void update_entity( Entity *ent )
{
  if( !ent || !ent->inuse ) return;
  
  if( ent->body )
  {
    Vec2_Copy( ent->body->position, ent->position );
    Vec2_Subtract( ent->position, ent->offset, ent->position );
  }
  if( ( ent->think_rate ) && ( Get_Time() % ent->think_rate == 0 ) )
  {
    if( ent->Think )
      ent->Think( ent );
  }
}


void update_all_entities()
{
  int i, e;

  do_steps( _ent_space );
  
  e = 0;
  for( i = 0; i < MAX_ENTITIES && e <= _num_ents; i++ )
  {
    if( _ent_list[ i ].inuse )
      update_entity( &_ent_list[ i ] );
  }
}


void draw_entity( Entity *ent )
{
  if( !ent || !ent->visible || !ent->inuse ) return;
  
  if( ent->Draw )
    ent->Draw( ent );

  if( ent->actors[ ent->draw_state ] )
    draw_actor( ent->actors[ ent->draw_state ] );
}


void draw_all_entities()
{
  int i, e;

  e = 0;
  for( i = 0; i < MAX_ENTITIES && e <= _num_ents; i++ )
  {
    if( _ent_list[ i ].inuse && _ent_list[ i ].visible )
      draw_entity( &_ent_list[ i ] );
  }
}


uint8 add_draw_state( Entity *ent, char *file, void ( *Finished )( struct entity_s *self ) )
{
  int i;
  
  if( !ent || !file ) return FALSE;
  
  for( i = 0; i < MAX_ACTORS; i++ )
  {
    if( !ent->actors[ i ] )
    {
      ent->actors[ i ] = create_actor( ent, file, Finished );
      return TRUE;
    }
  }
  
  return FALSE;
}


uint8 add_ent_to_space( Entity *ent )
{
  if( !ent || !ent->body ) return FALSE;
  
  if( !add_body( _ent_space, ent->body ) )
    return FALSE;
  
  return TRUE;
}


void remove_ent_from_space( Entity *ent )
{
  if( !ent || !ent->body )
    return;
  
  remove_body( _ent_space, ent->body );
}


/* eof */