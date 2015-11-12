#include "actor.h"
/*
typedef struct
{
	int			inuse;		
	struct entity_s		*owner;		
	char			*name;		
	Sprite			*sprite;	
	
	int			num_frames;	
	int			frame;		
	int			frame_rate;	
	int			start;		
	int			end;		
	
	int			direction;	
	int			type;		
	
	void			( *Finished )( struct entity_s *self );	
}Actor;*/

Actor* create_actor( char *file )
{
  Actor *new;
  Dict *config;
  
  config = Parse( file );
  if( !config )
  {
    Log( ERROR, "%s actor config file couldn't be parsed", file );
    return NULL;
  }
  
  new = g_new0( Actor, 1 );
  if( !new )
  {
    Log( ERROR, "Could allocate memory for actor %s", file );
    Free_Dict( &config );
    return NULL;
  }
  
  new->sprite = load_sprite_from_config( file );
  if( !new->sprite )
  {
    Free_Dict( &config );
    free_actor( &new );
    return NULL;
  }
  
  /* init stuff */
  new->direction = FORWARD;
  
  Free_Dict( &config );
  return new;
}


void draw_actor( Actor *actor )
{
  /* draw the actor */
  if( !( Get_Frame() % actor->frame_rate ) )
    draw_sprite( actor->sprite, actor->owner->position, actor->owner->position, actor->owner->position, actor->frame );
  
  /* call the finished function */
  if( ( actor->frame == actor->end ) && ( actor->Finished ) && ( !actor->done ) )
    actor->Finished( actor->owner );
    
  /* update the frame */
  if( actor->type != ANIM_NO )
  {
    actor->frame += actor->direction;
    actor->done = 1;
    
    /* make sure we don't go past the final frame or the first frame */
    if( actor->frame > actor->end )
    { 
      /* switch direction if oscillating, loop if looping, set the actor to the end frame if else */
      if( actor->type == ANIM_OSCI )
      {
	actor->direction = REVERSE;
	actor->frame = actor->end;
      }
      else if( actor->type == ANIM_LOOP )
	actor->frame = actor->start;
      else
	actor->frame = actor->end;
    }
    else if( actor->frame < actor->start )
    {
      /* switch direction if oscillating else set the actor to the starting frame if else */
      if( actor->type == ANIM_OSCI )
      {
	actor->direction = FORWARD;
	actor->frame = actor->start;
      }
      else
	actor->frame = actor->start;
    }
  }
}


void reset_actor( Actor *actor )
{
  actor->frame = actor->start;
  actor->direction = 1;
}


void free_actor( Actor **actor )
{
  Actor *tmp;
  
  if( !actor ) return;
  if( !*actor ) return;
  
  tmp = *actor;
  
  if( tmp->name )
    free( tmp->name );
    
  if( tmp->sprite )
    free_sprite( tmp->sprite );
  
  free( tmp );
  *actor = NULL;
}


/* eof */