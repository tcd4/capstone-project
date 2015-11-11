#ifndef __COLLISIONS__
#define __COLLISIONS__


/**
 * @file collisions.h
 * 
 * @brief contains functions for determining if there is a collision between two bodies
 */


#include "game_math.h"


/**
 * @brief checks to see if 2 rectangles are colliding
 * 
 * @param s1	the size of the 1st rectangle
 * @param p1	the position of the 1st rectangle
 * @param s2	the size of the 2st rectangle
 * @param p1	the position of the 2st rectangle
 * 
 * @return TRUE if there's collision, FALSE if else
 */
uint8 rect_rect_collision( vec2_t s1, vec2_t p1, vec2_t s2, vec2_t p2 );


#endif
