#ifndef __COMMANDS__
#define __COMMANDS__


/**
 * @file cmds.h
 * 
 * @brief handles player input
 */


#include <SDL.h>
#include <glib.h>
#include <glib/glist.h>

#include "logger.h"
#include "graphics2d.h"


typedef struct cmd_s
{
  uint8		inuse;		/**< determines if the command is being used */
  char		*name;		/**< the name of the command */
  int		id;		/**< the key to press for the command to happen */
  uint32	hold_time;	/**< the time needed to hold the key for the command to happen */
  uint32	time_pressed;	/**< the amount of time the key has been press */
  uint32	start_time;	/**< the time when the key was pressed */
  EventNotify	event;		/**< the function to call when the command is activated */
  dataptr	event_param;	/**< the parameter for the event function */
}Cmd;	


/**
 * @brief initializes the command system
 */
void init_cmd_system();

/**
 * @brief checks if the command system is initialized
 * 
 * @return TRUE if it is, FALSE if it isn't
 */
uint8 cmd_system_is_init();

/**
 * @brief checks all Cmds to see if any have been invoked
 */
void check_cmds( SDL_Event *event );

/**
 * @brief check a Cmd
 * 
 * @param cmd	the Cmd to update
 */
void check_cmd( SDL_Event *event, Cmd *cmd );

/**
 * @brief adds a Cmd
 * 
 * @param on	determines if the command will immediately be active
 * @param name	the name of the Cmd
 * @param id	the key to press for the Cmd to happen
 * @param hold	the time needed to hold the key for the Cmd to happen
 * @param event	the function to call when the command is activated 
 * @param param	the parameter for the event function
 * 
 * @return TRUE on success, FALSE on failure
 */
uint8 add_cmd( uint8 on, char *name, int id, uint32 hold, EventNotify event, dataptr param );

/**
 * @brief turns on a Cmd
 * 
 * @param name	the name of the Cmd to turn on
 */
void turn_on_cmd( char *name );

/**
 * @brief turns off a Cmd
 * 
 * @param name	the name of the Cmd to turn off
 */
void turn_off_cmd( char *name );

/**
 * @brief removes the Cmd for a certain key
 * 
 * @param name	the name of the Cmd to remove
 */
void remove_cmd_by_name( char *name );

/**
 * @brief turns off the command system
 */
void close_cmd_system();


#endif
