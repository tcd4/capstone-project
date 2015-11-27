#ifndef __PLAYER__
#define __PLAYER__


/**
 * @file player.h
 * 
 * @brief contains functions for player interactions
 */


#define ENT_PLAYER 1
#define PLAYER_GROUP 2


#include "entity.h"
#include "cmds.h"


/**< player states */
enum
{
  PLAYER_IDLE = 0,
  PLAYER_WALK,
  PLAYER_ATTACK,
  PLAYER_DIE,
};

/**< player flags */
enum
{
  GROUNDED = 0,
  FLYING = 1
};


/**
 * @brief creates a player entity
 * 
 * @param file	the config file to load the player from
 */
Entity* create_player( char *file );


#endif
