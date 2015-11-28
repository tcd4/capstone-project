#ifndef __ENEMY__
#define __ENEMY__


/**
 * @file enemy.h
 * 
 * @brief contains functions for enemy interactions
 */


#include "entity.h"


/**< enemy states */
enum
{
  ENEMY_IDLE = 0,
  ENEMY_WALK,
  ENEMY_ATTACK,
  ENEMY_DIE,
};


/**
 * @brief creates an enemy entity
 * 
 * @param file	the config file to load the enemy from
 * @param spawn	where to spawn the enemy on the screen
 */
void create_enemy( char *file, vec2_t spawn );


#endif