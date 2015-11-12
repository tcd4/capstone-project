#ifndef __GAME_MATH__
#define __GAME_MATH__


#include <math.h>
#include <SDL.h>

#include "types.h"


/* standard math defines */

/*< PI define */
#define PI 3.14159265

/*< TAU define */
#define TAU 6.283185308

/*< radian to degree conversion constant */
#define TODEG 57.2957795

/*< degree to radian conversion constant */
#define TORAD 0.0174532925

/*< converts an angle from radians to degrees */
#define Angle_To_Deg( a )                       ( a * TODEG )

/*< converts an angle from degrees to radians */
#define Angle_To_Rad( a )                       ( a * TORAD )


/* random macros */

/**
 * @brief random macro from Id Software's Quake 2 Source
 * This macro makes rand() more random
 *
 * @return a random float from 0 to 1.0
 */
#define random()	( ( rand() & 0x7fff ) / ( ( float )0x7fff ) )

/**
 * @brief random macro from Id Software's Quake 2 Source
 * 
 * @return a random float from -1.0 to 1.0
 */
#define crandom()	( 2.0 * ( random() - 0.5 ) )

/**
 * @brief random macro for integer values
 * 
 * @return a random int from 0 to 100
 */
#define irandom()	( ( int )( random() * 100 ) )

/**
 * @brief random macro for integer in a range of values
 * 
 * @param start	the starting value of the range
 * @param end	the ending value of the range
 * 
 * @return a int between start and end
 */
#define rand_ranged( start, end )	( ( int )( random() * ( end - start ) + start ) )


/* vector types */

/**< x axis define */
#define XA 0
/**< y axis define */
#define YA 1
/**< z axis define */
#define ZA 2
/**< a axis define */
#define AA 3

/*< 1d vector type */
typedef double vec_t;

/*< 2d vector type */
typedef vec_t vec2_t[ 2 ];

/*< 3d vector type */
typedef vec_t vec3_t[ 3 ];

/*< 4d vector type */
typedef vec_t vec4_t[ 4 ];


/* vector macros */

/*< sets a 2d vector */
#define Vec2_Set( v, a, b )			( v[ XA ] = a, v[ YA ] = b )

/*< subtracts 2 2d vectors */
#define Vec2_Subtract( a, b, c )	        ( c[ XA ] = a[ XA ] - b[ XA ], c[ YA ] = a[ YA ] - b[ YA ] )

/*< adds 2 2d vectors */
#define Vec2_Add( a, b, c )		        ( c[ XA ] = a[ XA ] + b[ XA ], c[ YA ] = a[ YA ] + b[ YA ] )

/*< finds the dot product of 2 2d vectors */
#define Vec2_Dot_Product( a, b )                ( a[ XA ] * b[ XA ] + a[ YA ] * b[ YA ] )

/*< copys 2d vector a into b */
#define Vec2_Copy( a, b )		        ( b[ XA ] = a[ XA ], b[ YA ] = a[ YA ] )

/*< sets a 2d vector to [ 0, 0 ] */
#define Vec2_Clear( a )			        ( a[ XA ] = 0, a[ YA ] = 0 )

/*< checks if 2 2d vectors are equal */
#define Vec2_Compare( a, b )		        ( ( a[ XA ] == b[ XA ] && a[ YA ] == b[ YA ] ) ? 1: 0 )

/*< checks if a 2d vector is zeroed */
#define Vec2_Zeroed( a )			( ( a[ XA ] == 0 && a[ YA ] == 0 ) ? 1: 0 )

/*< scales a 2d vector */
#define Vec2_Scale( dst, src, factor )          ( dst[ XA ] = src[ XA ] * factor, dst[ YA ] = src[ YA ] * factor )

/*< sets a 3d vector */
#define Vec3_Set( v, a, b, c )			( Vec2_Set( v, a, b ), v[ ZA ] = c )

/*< subtracts 2 3d vectors */
#define Vec3_Subtract( a, b, c )	        ( Vec2_Subtract( a, b, c ), c[ ZA ] = a[ ZA ] - b[ ZA ] )

/*< adds 2 3d vectors */
#define Vec3_Add( a, b, c )		        ( Vec2_Add( a, b, c ), c[ ZA ] = a[ ZA ] + b[ ZA ] )

/*< finds the dot product of 2 3d vectors */
#define Vec3_Dot_Product( a, b )                ( Vec2_Dot_Product( a, b ) + a[ ZA ] * b[ ZA ] )

/*< copys 3d vector a into b */
#define Vec3_Copy( a, b )		        ( Vec2_Copy( a, b ), b[ ZA ] = a[ ZA ] )

/*< sets a 3d vector to [ 0, 0, 0 ] */
#define Vec3_Clear( a )			        ( Vec2_Clear( a ), a[ ZA ] = 0 )

/*< checks if 2 3d vectors are equal */
#define Vec3_Compare( a, b )		        ( ( Vec2_Compare( a, b ) && a[ ZA ] == b[ ZA ] ) ? 1: 0 )

/*< checks if a 3d vector is zeroed */
#define Vec3_Zeroed( a )			( ( a[ XA ] == a[ YA ] == a[ ZA ] == 0 ) ? 1: 0 )

/*< scales a 3d vector */
#define Vec3_Scale( dst, src, factor )          ( Vec2_Scale( dst, src, factor ), dst[ ZA ] = src[ ZA ] * factor )

/*< sets a 4d vector */
#define Vec4_Set( v, a, b, c, d )		( Vec3_Set( v, a, b, c ), v[ AA ] = d )

/*< subtracts 2 4d vectors */
#define Vec4_Subtract( a, b, c )	        ( Vec3_Subtract( a, b, c ), c[ AA ] = a[ AA ] - b[ AA ] )

/*< adds 2 4d vectors */
#define Vec4_Add( a, b, c )		        ( Vec3_Add( a, b, c ), c[ AA ] = a[ AA ] + b[ AA ] )

/*< finds the dot product of 2 4d vectors */
#define Vec4_Dot_Product( a, b )                ( Vec3_Dot_Product( a, b ) + a[ AA ] * b[ AA ] )

/*< copys 4d vector a into b */
#define Vec4_Copy( a, b )		        ( Vec3_Copy( a, b ), b[ AA ] = a[ AA ] )

/*< sets a 4d vector to [ 0, 0, 0, 0 ] */
#define Vec4_Clear( a )			        ( Vec3_Clear( a ), a[ AA ] = 0 )

/*< checks if 2 4d vectors are equal */
#define Vec4_Compare( a, b )		        ( ( Vec3_Compare( a, b ) && a[ AA ] == b[ AA ] ) ? 1: 0 )

/*< checks if a 4d vector is zeroed */
#define Vec4_Zeroed( a )			( ( a[ XA ] == a[ YA ] == a[ ZA ] == a[ AA ] == 0 ) ? 1: 0 )

/*< scales a 4d vector */
#define Vec4_Scale( dst, src, factor )          ( Vec3_Scale( dst, src, factor ), dst[ AA ] = src[ AA ] * factor )



/* vector functions */


/**
 * @brief normalizes a vector
 *
 * @param v	the vector to normalize
 */
void Vec2_Normalize( vec2_t *v );

/**
 * @brief gets the magnitude of a vector
 *
 * @param v	the vector to use
 *
 * @return the magnitude of a vector
 */
float Vec2_Get_Magnitude( vec2_t v );

/**
 * @brief normalizes a vector then sets its magnitude
 *
 * @param v	the vector to use
 * @param m	the magnitude to set the vector to
 */
void Vec2_Set_Magnitude( vec2_t *v, float m );

/**
 * @brief compares the magnitudes of 2 vectors
 *
 * @param v1	the 1st vector to compare
 * @param v2	the 2nd vector to compare
 *
 * @return 1 if v1 > v2, 0 if v1 == v2, -1 if v1 < v2
 */
int8 Vec2_Magnitude_Compare( vec2_t v1, vec2_t v2 );

/**
 * @brief gets the distance between 2 vectors
 *
 * @param v1	the 1st vector to use
 * @param v2	the 2nd vector to use
 *
 * @return the distance between the 2 vectors
 */
uint32 Vec2_Distance_Between( vec2_t v1, vec2_t v2 );

/**
 * @brief sets the angle of a vector
 *
 * @param v	the vector to use
 * @param a	the angle ( in degrees ) to use
 */
void Vec2_Set_Angle_Degs( vec2_t *v, float a );

/**
 * @brief sets the angle of a vector
 *
 * @param v	the vector to use
 * @param a	the angle ( in radians ) to use
 */
void Vec2_Set_Angle_Rads( vec2_t *v, float a );

/**
 * @brief normalizes a vector
 *
 * @param v	the vector to normalize
 */
void Vec3_Normalize( vec3_t *v );

/**
 * @brief gets the magnitude of a vector
 *
 * @param v	the vector to use
 *
 * @return the magnitude of a vector
 */
float Vec3_Get_Magnitude( vec3_t v );

/**
 * @brief normalizes a vector then sets its magnitude
 *
 * @param v	the vector to use
 * @param m	the magnitude to set the vector to
 */
void Vec3_Set_Magnitude( vec3_t *v, float m );

/**
 * @brief compares the magnitudes of 2 vectors
 *
 * @param v1	the 1st vector to compare
 * @param v2	the 2nd vector to compare
 *
 * @return 1 if v1 > v2, 0 if v1 == v2, -1 if v1 < v2
 */
int8 Vec3_Magnitude_Compare( vec3_t v1, vec3_t v2 );

/**
 * @brief gets the distance between 2 vectors
 *
 * @param v1	the 1st vector to use
 * @param v2	the 2nd vector to use
 *
 * @return the distance between the 2 vectors
 */
uint32 Vec3_Distance_Between( vec3_t v1, vec3_t v2 );

/**
 * @brief sets the angle of a vector
 *
 * @param v	the vector to use
 * @param a	the angle ( in degrees ) to use
 */
void Vec3_Set_Angle_Degs( vec3_t *v, float a );

/**
 * @brief sets the angle of a vector
 *
 * @param v	the vector to use
 * @param a	the angle ( in radians ) to use
 */
void Vec3_Set_Angle_Rads( vec3_t *v, float a );

/**
 * @brief normalizes a vector
 *
 * @param v	the vector to normalize
 */
void Vec4_Normalize( vec4_t *v );

/**
 * @brief gets the magnitude of a vector
 *
 * @param v	the vector to use
 *
 * @return the magnitude of a vector
 */
float Vec4_Get_Magnitude( vec4_t v );

/**
 * @brief normalizes a vector then sets its magnitude
 *
 * @param v	the vector to use
 * @param m	the magnitude to set the vector to
 */
void Vec4_Set_Magnitude( vec4_t *v, float m );

/**
 * @brief compares the magnitudes of 2 vectors
 *
 * @param v1	the 1st vector to compare
 * @param v2	the 2nd vector to compare
 *
 * @return 1 if v1 > v2, 0 if v1 == v2, -1 if v1 < v2
 */
int8 Vec4_Magnitude_Compare( vec4_t v1, vec4_t v2 );

/**
 * @brief gets the distance between 2 vectors
 *
 * @param v1	the 1st vector to use
 * @param v2	the 2nd vector to use
 *
 * @return the distance between the 2 vectors
 */
uint32 Vec4_Distance_Between( vec4_t v1, vec4_t v2 );

/**
 * @brief sets the angle of a vector
 *
 * @param v	the vector to use
 * @param a	the angle ( in degrees ) to use
 */
void Vec4_Set_Angle_Degs( vec4_t *v, float a );

/**
 * @brief sets the angle of a vector
 *
 * @param v	the vector to use
 * @param a	the angle ( in radians ) to use
 */
void Vec4_Set_Angle_Rads( vec4_t *v, float a );


/* standard math functions */

/**
 * @brief calculates an angle from an x and a y
 *
 * @param x	the length to use
 * @param y	the height to use
 *
 * @return an angle in degrees
 */
float Get_Angle_Deg( float x, float y );

/**
 * @brief calculates an angle from an x and a y
 *
 * @param x	the length to use
 * @param y	the height to use
 *
 * @return an angle in radians
 */
float Get_Angle_Rad( float x, float y );

/**
 * @brief calculates the cross product of 2 3d vectors
 *
 * @param out	the output vector
 * @param v1	the 1st vector to use
 * @param v2	the 2nd vector to use
 */
void Cross_Product( vec3_t *out, vec3_t v1, vec3_t v2 );


/* shapes */

/**< the type of shapes that are supported */
typedef enum
{
  NO_SHAPE = 0,
  POINT = 1,
  RECTANGLE = 2,
  CIRCLE = 4,
  CUSTOM = 7
}Shape;

/* rectangles */

typedef struct
{
  double x,y,w,h;
}Rect;

void set_rect( SDL_Rect *r, double x, double y, double w, double h );


/* circles */

typedef struct
{
  int		x;	/** the x coordintate */
  int		y;	/** the y coordintate */
  uint32	r;	/** the radius */
}Circ;


#endif