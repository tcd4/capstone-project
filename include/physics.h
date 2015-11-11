#ifndef __PHYSICS__
#define __PHYSICS__


#include <glib.h>
#include <glib/glist.h>

#include "entity.h"
#include "collisions.h"


/* basic collision group defines */
#define NO_GROUP 0
#define ALL_GROUPS 1


/**< the bodies in 2d space */
typedef struct body_s
{
  struct entity_s	*owner;		/**< the entity whose body this is */
  uint32		group;		/**< the collision group the body belongs to */
  
  vec2_t		position;	/**< the position of the body in space */
  vec2_t		velocity;	/**< the velocity of the body in space */
  vec2_t		acceleration;	/**< the acceleration of the body in space */
  vec2_t		size;		/**< the width and height of the body */
  
  CollisionNotify	collide;	/**< the function to call when the body collides with another body */
}Body;


/**< the space for handling physics */
typedef struct space_s Space;


/**
 * @brief creates a new body
 * 
 * @param owner		the entity whose body this will be
 * @param group		the collision group the body belongs to
 * @param shape_type	the shape of the body
 * @param shape		the struct for the shape
 * @param position	the starting position of the body in space
 * @param velocity	the starting velocity of the body in space
 * @param acceleration	the starting acceleration of the body in space
 * @param collide	the function to call when the body collides with another body
 * 
 * @return a pointer to the newly created body or NULL on error
 */
Body* create_body( struct entity_s *owner, uint32 group, vec2_t size, vec2_t position, vec2_t velocity, vec2_t acceleration, CollisionNotify collide );

/**
 * @brief frees a body
 * 
 * @param body	the body to free
 */
void free_body( Body **body );


/**
 * @brief creates a new physics space
 * 
 * @param steps	the number of steps to do per instance of physics
 * 
 * @return a pointer to the new space or NULL on error
 */
Space* create_space( uint8 steps );

/**
 * @brief frees a space
 * WARNING this will not free the bodies in the space
 * 
 * @param space	the space to free
 */
void free_space( Space **space );

/**
 * @brief move bodies in the space and checks for collisions between them
 * 
 * @param space	the space to move
 */
void do_steps( Space *space );

/**
 * @brief adds a body to the physics space
 * 
 * @param space	the space to add to
 * @param body	the body to add
 * 
 * @return TRUE on success or FALSE on failure
 */
uint8 add_body( Space *space, Body *body );

/**
 * @brief removes a body from physics space
 * 
 * @param space	the space to remove from
 * @param body	the body to remove
 */
void remove_body( Space *space, Body *body );


#endif