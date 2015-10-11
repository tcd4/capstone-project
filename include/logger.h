#ifndef __LOGGER__
#define __LOGGER__


/**
 * @file logger.h
 * 
 * @brief contains functions for logging
 */


#include <SDL.h>
#include <glib/gprintf.h>

#include "types.h"


/**< the various logging levels */
typedef enum 
{
  NONE = 0,
  FATAL = 1,
  ERROR = 2,
  WARN = 4,
  TRACE = 8,
  INFO = 16,
  ALL = 31
}Log_Level;


/**< flag to check for if the logger is initialized */
#define LOGGER_INIT	1

/**< flag to check for if the logger is threaded */
#define LOGGER_THREADED	2

/**< flag to check for if the logger is finished */
#define LOGGER_DONE	4

/**
 * @brief initializes the logger
 * 
 * @param filename	output file or stdout if none given
 * @param threaded	determines if threading should be used
 */
void	Init_Logger( char *filename, uint8 threaded );

/**
 * @brief checks if the logger is initialized
 */
uint8	Logger_Is_Init();

/**
 * @brief enables threading
 */
void	Enable_Threaded_Logger();

/**
 * @brief checks if the logger is multi-threaded
 */
uint8	Logger_Is_Threaded();

/**
 * @brief if the logger is using threading, stop the thread
 */
void	Exit_Logging();

/**
 * @brief logs a message to the log file
 * 
 * @param lvl	the Log_Level of the message
 * @param msg	the message with tokens
 * @param ...	the variables for the msg
 */
#define Log( lvl, ... )		Log_Msg( __FILE__, __LINE__, lvl, __VA_ARGS__ )
void Log_Msg( char *file, int line, Log_Level lvl, char *msg, ... );

/**
 * @brief converts a Log_Level to a string
 * 
 * @param lev	the log level to convert
 *
 * @return a string representation of a Log_Level
 */
char* Log_Level_To_Str( Log_Level lev );


#endif