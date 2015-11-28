#ifndef __PLAYER__
#define __PLAYER__


/**
 * @file player.h
 * 
 * @brief contains functions for player interactions
 */


#define PLAYER_GROUP 2


#include "entity.h"
#include "cmds.h"


/**< player states */
enum
{
  PLAYER_IDLE = 0,
  PLAYER_WALK,
  PLAYER_JUMP,
  PLAYER_ATTACK,
  PLAYER_DIE,
};

/**< player flags */
enum
{
  PLAYER_NONE = 0,
  PLAYER_GROUNDED = 1,
  PLAYER_FLYING = 2,
  PLAYER_ATTACKING = 4
};


/**
 * @brief creates a player entity
 * 
 * @param file	the config file to load the player from
 */
Entity* create_player( char *file );


#endif
