#ifndef __GRAPHICS_2D__
#define __GRAPHICS_2D__


/**
 * @file graphics2d.h
 * 
 * @brief handles displaying graphics in 2 dimensions
 */


#include <SDL.h>
#include <SDL_image.h>

#include "types"


void Init_Graphics( Dict *config );
void Frame_Delay();
void ResetBuffer();
void Next_Frame();


#endif