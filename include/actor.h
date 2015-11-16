#ifndef __ACTOR__
#define __ACTOR__


/**
 * @file actor.h
 * 
 * @brief controls animations of sprites
 */


#include "entity.h"
#include "parser.h"
#include "sprite.h"


#define FORWARD 1
#define REVERSE -1


/**< animation types */
typedef enum
{
	ANIM_NO		= 0,
	ANIM_PASS	= 1,
	ANIM_LOOP	= 2,
	ANIM_OSCI	= 3
}Anim_Type;


/**< animation handler */
typedef struct actor_s
{
	int			inuse;		/**< determines if the actor is being used */
	int			done;		/**< determines if the animation finished */
	struct entity_s		*owner;		/**< pointer to the entity that does has this animation */
	char			*name;		/**< the name of the animation */
	Sprite			*sprite;	/**< the spritesheet for the animation */
	
	int			num_frames;	/**< the number of frames the actor uses */
	int			frame;		/**< the current frame the actor is on */
	int			frame_rate;	/**< how often the animation updates */
	int			start;		/**< the frame to start on */
	int			end;		/**< the frame to end on */
	
	uint8			direction;	/**< the direction the animation is being player */
	int			type;		/**< the Anim_Type the actor is */
	
	void			( *Finished )( struct entity_s *self );	/**< the function to call when the animation finishes */
}Actor;


/**
 * @brief creates a new actor
 * 
 * @param owner		the owner of the actor
 * @param file		the file to load the actor from
 * @param Finished	the function to call when the animation is over
 *
 * @return a pointer to the newly created actor or NULL
 */
Actor* create_actor( struct entity_s *owner, char *file, void ( *Finished )( struct entity_s *self ) );

/**
 * @brief draws an actor to the screen
 * 
 * @param actor	the actor to draw
 */
void draw_actor( Actor *actor );

/**
 * @brief resets an actor's direction and current frame
 * 
 * @param actor	the actor to reset
 */
void reset_actor( Actor *actor );

/**
 * @brief frees the memory from an actor
 * 
 * @param actor	 the actor to free
 */
void free_actor( Actor **actor );


#endif