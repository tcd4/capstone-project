#ifndef __SPRITE__
#define __SPRITE__


/**
 * @file sprite.h
 * 
 * @brief contains support for handling sprites
 */


#include <SDL.h>
#include <SDL_image.h>

#include "graphics2d.h"
#include "logger.h"
#include "parser.h"


#define MAX_SPRITES 255


typedef struct sprite_s Sprite;


/**
 * @brief initializes the sprite system
 */
void init_sprite_system();

/**
 * @brief closes the sprite system
 */
void close_sprite_system();

/**
 * @brief loads a sprite from a config file
 * 
 * @param file	the config file to load from
 * 
 * @return the loaded sprite or NULL on error
 */
Sprite* load_sprite_from_config( char *file );

/**
 * @brief loads a sprite
 * 
 * @param image_file	the name of the image file to load
 * @param cols		the number of columns in the spritesheet
 * @param rows		the number of rows in the spritesheet
 * @param frames	the number of frames in the spritesheet
 * @param dynamic	determines if the sprite is dynamically freed
 * 
 * @return the loaded sprite or NULL on error
 */
Sprite* load_sprite( char *image_file, uint32 cols, uint32 rows, uint32 frames, uint8 dynamic );

/**
 * @brief frees a sprite
 * 
 * @param sprite	the sprite to free
 */
void free_sprite( Sprite *sprite );

/**
 * @brief draws a sprite onto the screen
 * 
 * @param sprite	the sprite to draw
 * @param position	where to draw the sprite
 * @param scale		how big to draw the sprite
 * @param rotation	the rotation to draw the sprite
 * @param frame		the frame in the sprite to draw
 */
void draw_sprite( Sprite *sprite, vec2_t position, vec2_t scale, vec2_t rotation, uint32 frame );


#endif