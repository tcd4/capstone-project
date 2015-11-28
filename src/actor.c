#include "actor.h"


Actor* create_actor( struct entity_s *owner, char *file, void ( *Finished )( struct entity_s *self ) )
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
  
  new->sprite = load_sprite_from_config( Find_In_Dict( config, "sprite" ) );
  if( !new->sprite )
  {
    Free_Dict( &config );
    free_actor( &new );
    return NULL;
  }
  
  new->name = strdup( Find_In_Dict( config, "name" ) );
  Str_As_Int( Find_In_Dict( config, "start" ), &new->start );
  Str_As_Int( Find_In_Dict( config, "end" ), &new->end );
  Str_As_Int( Find_In_Dict( config, "frame_rate" ), &new->frame_rate );
  Str_As_Int( Find_In_Dict( config, "type" ), &new->type );
  
  new->owner = owner;
  new->frame = new->start;
  new->num_frames = new->end - new->start;
  new->direction = FORWARD;
  new->Finished = Finished;
  
  Free_Dict( &config );
  return new;
}


void draw_actor( Actor *actor )
{
  if( !actor ) return;

  draw_sprite( actor->sprite, actor->owner->position, actor->owner->scale, actor->owner->rotation, actor->frame );
  
  /* make sure to only update with the frame rate */
  if( Get_Frame() % actor->frame_rate ) return;
  
  if( actor->type == ANIM_NO ) return;
  
  /* call the finished function if the animation is over */
  if( ( actor->frame == actor->end ) && ( actor->Finished ) && ( !actor->done ) )
  {
    actor->Finished( actor->owner );
    actor->done = 1;
  }
    
  /* update the frame */
  actor->frame += actor->direction;
  
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


void reset_actor( Actor *actor )
{
  actor->frame = actor->start;
  actor->direction = FORWARD;
  actor->done = 0;
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