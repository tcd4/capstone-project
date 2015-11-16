#ifndef __GRAPHICS_2D__
#define __GRAPHICS_2D__


/**
 * @file graphics2d.h
 * 
 * @brief handles displaying graphics in 2 dimensions
 */


#include <SDL.h>

#include "parser.h"
#include "logger.h"
#include "game_math.h"


/**
 * @brief initializes a 2d graphics
 * 
 * @param config	the Dict to create the window with
 */
void Init_2DGraphics( Dict *config );

/** 
 * @brief closes the graphics system
 */
void Close_2DGraphics();

/**
 * @brief renders the contents currently in the screen buffer
 */
void Next_Frame();

/**
 * @brief clears the frame buffer
 */
void Clear_Frame();

/**
 * @brief gets a pointer to the game screen
 * 
 * @return a pointer to the game screen or NULL on error
 */
SDL_Surface* Get_Screen();

/**
 * @brief gets a pointer to the game renderer
 * 
 * @return a pointer to the game renderer or NULL on error
 */
SDL_Renderer* Get_Renderer();

/**
 * @brief gets the time the game has been running
 * 
 * @return the amount of the time the game has been running
 */
uint32 Get_Time();

/**
 * @brief gets the current frame number
 * 
 * @return the current frame number
 */
uint32 Get_Frame();

/**
 * @brief gets the resolution of the main window
 * 
 * @return the resolution of the main window
 */
vec2_t* Get_Resolution();


#endif