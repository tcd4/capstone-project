#ifndef __ENTITY__
#define __ENTITY__


/**
 * @file entity.h
 * 
 * @brief contains the entity system
 * 
 * Entities are classified as any objects in the game world 
 * that interact with the rest of the world.
 */


#include "sprite.h"
#include "physics.h"

#define MAX_ENTITIES 128
#define PHYSICS_STEPS 5


enum
{
  STATE_NONE = 0,
  STATE_ALIVE = 1,
  STATE_DUMB = 2,
  STATE_DEAD = 4,
  STATE_STATIONARY = 8,
  STATE_ALL = 15
};


typedef struct entity_s
{
	int			inuse;		/**< determines if the entities is in use */

	char			*name;		/**< name of the entity type */

	struct entity_s		*self;		/**< pointer to itself */
	struct entity_s		*owner;		/**< pointer to the entity that owns this one */

	/* need actor stuff */
	
	uint16			state;		/**< the state of the entity */
	uint8			visible;	/**< determines if the entity is drawn or not */
	
	struct body_s		*body;
	vec2_t			position;	/**< position of the entity */
	vec2_t			origin;		/**< center of the entity */

	Uint32			thinkrate;	/**< determines how often the entity thinks */
	Uint32			nextThink;	/**< determines when the entity will think next */

	void			( *Draw )( struct entity_s *self );				/**< pointer to the entity's draw function */
	void			( *Free )( struct entity_s *self );				/**< pointer to the entity's free function */
	void			( *Think )( struct entity_s *self );				/**< pointer to the entity's think function */
	void			( *Touch )( struct entity_s *self, struct entity_s *other );	/**< pointer to the entity's collision function */
	void			( *Die )( struct entity_s *self );				/**< pointer to the entity's death function */
	void			( *Move )( struct entity_s *self );				/**< pointer to the entity's move function */
}Entity;


/**
 * @brief initializes all the entities to nothing
 */
void init_entity_system();

/**
 * @brief closes the entity system and frees all entities
 */
void close_entity_system();

/**
 * @brief initializes new entities
 *
 * @return a pointer to the new entity or NULL on error
 */
Entity* create_entity();

/**
 * @brief frees an entity
 * 
 * @param ent	the entity to free
 */
void free_entity( Entity *ent );

/**
 * @brief frees all the entities
 */
void free_all_entities();

/**
 * @brief updates an entity and calls its think function
 * 
 * @param ent	the entity to update
 */
void update_entity( Entity *ent );

/**
 * @brief updates all the entities
 */
void update_all_entities();

/**
 * @brief draws an entity to the screen
 * 
 * @param ent	the entity to draw
 */
void draw_entity( Entity *ent );

/**
 * @brief draws all the entities to the screen
 */
void draw_all_entities();


#endif