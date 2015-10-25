#ifndef __STR_CONVERT__
#define __STR_CONVERT__


/**
 * @file str_conversions.h
 * 
 * @brief contains functions for converting strings to numbers
 */


#include <stdio.h>

#include "types.h"
#include "game_math.h"


/**
 * @brief converts a string to an int
 * 
 * @param s	the string to convert
 * @param out	the output variable
 * 
 * @return 1 on success or 0 on failure
 */
uint8 Str_As_Int( char *s, int *out );

/**
 * @brief converts a string to an uint
 * 
 * @param s	the string to convert
 * @param out	the output variable
 * 
 * @return 1 on success or 0 on failure
 */
uint8 Str_As_UInt( char *s, uint32 *out );

/**
 * @brief converts a string to a float
 * 
 * @param s	the string to convert
 * @param out	the output variable
 * 
 * @return 1 on success or 0 on failure
 */
uint8 Str_As_Float( char *s, float *out );

/**
 * @brief converts a string to a double
 * 
 * @param s	the string to convert
 * @param out	the output variable
 * 
 * @return 1 on success or 0 on failure
 */
uint8 Str_As_Double( char *s, double *out );

/**
 * @brief converts a string to a vec2_t
 * 
 * @param s	the string to convert
 * @param out	the output variable
 * 
 * @return 1 on success or 0 on failure
 */
uint8 Str_As_Vec2( char *s, vec2_t *out );

/**
 * @brief converts a string to a vec3_t
 * 
 * @param s	the string to convert
 * @param out	the output variable
 * 
 * @return 1 on success or 0 on failure
 */
uint8 Str_As_Vec3( char *s, vec3_t *out );

/**
 * @brief converts a string to a vec4_t
 * 
 * @param s	the string to convert
 * @param out	the output variable
 * 
 * @return 1 on success or 0 on failure
 */
uint8 Str_As_Vec4( char *s, vec4_t *out );


#endif