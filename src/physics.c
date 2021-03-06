#include "physics.h"
#include "collisions.h"


struct space_s
{
  GSList	*bodies;		/**< a list of bodies in the space */
  uint8		steps;		/**< the number of steps the space should perform per frame */
  double	step_factor;	/**< how much physics is scaled down per step */
};


static void _do_step( Space *space );
static void _update_body( Space *space, Body *body );
static void _check_for_collisions( Space *space, Body *body, double *moved );


Body* create_body( struct entity_s *owner, uint32 group, vec2_t size, vec2_t position, CollisionNotify collide )
{
  Body *new;
  
  new = g_new0( Body, 1 );
  if( !new )
  {
    Log( WARN, "The body for %s could not be created.", owner->name );
    return NULL;
  }
  
  new->owner = owner;
  new->group = group;
  new->collide = collide;
  
  Vec2_Copy( size, new->size );
  Vec2_Copy( position, new->position );
  
  return new;
}


void free_body( Space *space, Body **body )
{
  Body *tmp;
  
  if( !body ) return;
  if( !*body ) return;

  tmp = *body;
  remove_body( space, tmp );
  free( tmp );
  *body = NULL;
}


Space* create_space( uint8 steps )
{
  Space *new;
  
  Log( INFO, "Creating space." );
  
  new = g_new0( Space, 1 );
  if( !new )
  {
    Log( WARN, "Failed to create space." );
    return NULL;
  }
  
  new->steps = steps;
  new->step_factor = 1.0 / steps;
  
  Log( INFO, "Space created." );
  
  return new;
}


void free_space( Space **space )
{
  Space *tmp;
  
  if( !space ) return;
  if( !*space ) return;
  
  tmp = *space;
  
  g_slist_free( tmp->bodies );
  free( tmp );
  *space = NULL;
}


void do_steps( Space *space )
{
  if( !space ) return;
  if( !space->bodies ) return;
  
  int i;
  
  for( i = 0; i < space->steps; i++ )
  {
    _do_step( space );
  }
}


void _do_step( Space *space )
{
  GSList *iter;
  
  for( iter = space->bodies; iter != NULL; iter = iter->next )
  {
    if( !iter->data ) continue;
    
    _update_body( space, ( Body* )iter->data );
  }
}


void _update_body( Space *space, Body *body )
{
  vec2_t step_vector_accel;
  vec2_t step_vector_vel;
  
  /* don't need to update anything on an unmoving body */
  if( Vec2_Zeroed( body->acceleration ) && Vec2_Zeroed( body->velocity ) ) return;
  
  /* scale the movement down to compensate for multiple steps */
  Vec2_Scale( step_vector_accel, body->acceleration, space->step_factor );
  Vec2_Scale( step_vector_vel, body->velocity, space->step_factor );
  
  /* move the body */
  Vec2_Add( step_vector_vel, step_vector_accel, step_vector_vel );
  Vec2_Add( body->velocity, step_vector_accel, body->velocity );
  Vec2_Add( step_vector_vel, body->position, body->position );
  
  /* nothing leaves the screen */
  if( body->position[ XA ] < 0 )
    body->position[ XA ] = 0;
  else if( body->position[ XA ] + body->size[ XA ] > 1920 )
    body->position[ XA ] = 1920 - body->size[ XA ];
  
  if( body->position[ YA ] < 0 )
    body->position[ YA ] = 0;
  else if( body->position[ YA ] + body->size[ YA ] > 1080 )
    body->position[ YA ] = 1080 - body->size[ YA ];

  _check_for_collisions( space, body, step_vector_vel );
}


void _check_for_collisions( Space *space, Body *body, double *moved )
{
  GSList *iter = NULL;
  Body *other;
  
  for( iter = space->bodies; iter != NULL; iter = iter->next )
  {
    if( !iter->data ) continue;
    if( iter->data == body ) continue;
    
    other = ( Body* ) iter->data;
    
    if( other->group == body->group ) continue;
    
    if( rect_rect_collision( body->size, body->position, other->size, other->position ) )
    {
      if( body->collide )
	body->collide( body->owner, other->owner, moved );
      
      if( other->collide )
	other->collide( other->owner, body->owner, moved );
    }
  }
}


uint8 add_body( Space *space, Body *body )
{
  GSList *tmp;
  if( !space ) return FALSE;
  if( !body ) return FALSE;
  
  tmp = g_slist_append( space->bodies, body );
  if( !tmp ) return FALSE;
  
  space->bodies = tmp;
  return TRUE;
}


void remove_body( Space *space, Body *body )
{
  if( !space ) return;
  if( !body ) return;
  
  space->bodies = g_slist_remove( space->bodies, body );
}


/* eof */