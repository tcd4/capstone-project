#ifndef __LEVEL
#define __LEVEL__


/**
 * @file level.h
 * 
 * @brief contains functions for level interactions
 */


#include <glib.h>
#include <glib/glist.h>

#include "entity.h"
#include "player.h"
#include "enemy.h"


#define ENT_WORLD 0
#define ENT_PLAYER 1
#define ENT_ENEMY 2
#define ENT_ATTACK_BOX 3


typedef struct level_s
{
  Sprite	*bg;		/**< the background image for the level */
  vec2_t	position;	/**< the position of the level in the world */
  vec2_t	scale;		/**< the scale of the level in the world */
  vec2_t	rotation;	/**< the rotation of the level in the world */
}Level;


/**
 * @brief loads a level
 * 
 * @param file	the def file to load the level from
 */
Level* load_level( char *file );

/**
 * @brief frees a level
 *
 * @param level	the level to free
 */
void free_level( Level **level );

/**
 * @brief draws the level
 * 
 * @param level	the level to draw
 */
void draw_level( Level *level );

/**
 * @brief gets the player entity
 */
Entity* get_player();


#endif