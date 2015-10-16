#include "game_math.h"


float Get_Angle_Deg( float x, float y )
{    
    return Angle_To_Deg( atan2( y, x ) + PI );
}


float Get_Angle_Rad( float x, float y )
{
    return ( atan2( y, x ) + PI ) ;
}


void Cross_Product( vec3_t *out, vec3_t v1, vec3_t v2 )
{
    *out[ 0 ] = v1[ 1 ] * v2[ 2 ] - v1[ 2 ] * v2[ 1 ];
    *out[ 1 ] = v1[ 2 ] * v2[ 0 ] - v1[ 0 ] * v2[ 2 ];
    *out[ 2 ] = v1[ 0 ] * v2[ 1 ] - v1[ 1 ] * v2[ 0 ];
}

void Vec2_Normalize( vec2_t *v )
{
    float m;

    g_return_if_fail( v );

    m = Vec2_Get_Magnitude( *v );
    g_return_if_fail( m != 0.0f );
    m = 1 / m;

    *v[ 0 ] *= m;
    *v[ 1 ] *= m;
}


float Vec2_Get_Magnitude( vec2_t v )
{
    return sqrt( v[ 0 ] * v[ 0 ] + v[ 1 ] * v[ 1 ] );
}


void Vec2_Set_Magnitude( vec2_t *v, float m )
{
    g_return_if_fail( v );

    Vec2_Normalize( v );
    
    *v[ 0 ] *= m;
    *v[ 1 ] *= m;
}


int8 Vec2_Magnitude_Compare( vec2_t v1, vec2_t v2 )
{
    float m1, m2;

    m1 = Vec2_Get_Magnitude( v1 );
    m2 = Vec2_Get_Magnitude( v2 );

    if( m1 > m2 ) return 1;
    else if( m1 < m2 ) return -1;
    else return 0;
}


uint32 Vec2_Distance_Between( vec2_t v1, vec2_t v2 )
{
    Vec2_Subtract( v1, v2, v1 );

    return fabs( Vec2_Get_Magnitude( v1 ) );
}


void Vec2_Set_Angle_Degs( vec2_t *v, float a )
{
    g_return_if_fail( v );

    a = Angle_To_Rad( a );

    *v[ 0 ] = cos( a );
    *v[ 1 ] = sin( a );
}


void Vec2_Set_Angle_Rads( vec2_t *v, float a )
{
    g_return_if_fail( v );

    *v[ 0 ] = cos( a );
    *v[ 1 ] = sin( a );
}


void Vec3_Normalize( vec3_t *v )
{
    float m;

    g_return_if_fail( v );

    m = Vec3_Get_Magnitude( *v );
    g_return_if_fail( m != 0.0f );
    m = 1 / m;

    *v[ 0 ] *= m;
    *v[ 1 ] *= m;
    *v[ 2 ] *= m;
}


float Vec3_Get_Magnitude( vec3_t v )
{
    return sqrt( v[ 0 ] * v [ 0 ] + v[ 1 ] * v[ 1 ] + v[ 2 ] * v[ 2 ] );
}


void Vec3_Set_Magnitude( vec3_t *v, float m )
{
    g_return_if_fail( v );

    Vec3_Normalize( v );
    
    *v[ 0 ] *= m;
    *v[ 1 ] *= m;
    *v[ 2 ] *= m;
}


int8 Vec3_Magnitude_Compare( vec3_t v1, vec3_t v2 )
{
    float m1, m2;

    m1 = Vec3_Get_Magnitude( v1 );
    m2 = Vec3_Get_Magnitude( v2 );

    if( m1 > m2 ) return 1;
    else if( m1 < m2 ) return -1;
    else return 0;
}


uint32 Vec3_Distance_Between( vec3_t v1, vec3_t v2 )
{
    Vec3_Subtract( v1, v2, v1 );

    return fabs( Vec3_Get_Magnitude( v1 ) );
}


void Vec3_Set_Angle_Degs( vec3_t *v, float a )
{
    g_return_if_fail( v );

    a = Angle_To_Rad( a );

    *v[ 0 ] = cos( a );
    *v[ 1 ] = sin( a );
}


void Vec3_Set_Angle_Rads( vec3_t *v, float a )
{
    g_return_if_fail( v );

    *v[ 0 ] = cos( a );
    *v[ 1 ] = sin( a );
}


void Vec4_Normalize( vec4_t *v )
{
    float m;

    g_return_if_fail( v );

    m = Vec4_Get_Magnitude( *v );
    g_return_if_fail( m != 0.0f );
    m = 1 / m;

    *v[ 0 ] *= m;
    *v[ 1 ] *= m;
    *v[ 2 ] *= m;
    *v[ 3 ] *= m;
}


float Vec4_Get_Magnitude( vec4_t v )
{
    return sqrt( v[ 0 ] * v[ 0 ] + v[ 1 ] * v[ 1 ] + v[ 2 ] * v[ 2 ] + v[ 3 ] * v[ 3 ] );
}


void Vec4_Set_Magnitude( vec4_t *v, float m )
{
    g_return_if_fail( v );

    Vec4_Normalize( v );
    
    *v[ 0 ] *= m;
    *v[ 1 ] *= m;
    *v[ 2 ] *= m;
    *v[ 3 ] *= m;
}


int8 Vec4_Magnitude_Compare( vec4_t v1, vec4_t v2 )
{
    float m1, m2;

    m1 = Vec4_Get_Magnitude( v1 );
    m2 = Vec4_Get_Magnitude( v2 );

    if( m1 > m2 ) return 1;
    else if( m1 < m2 ) return -1;
    else return 0;
}


uint32 Vec4_Distance_Between( vec4_t v1, vec4_t v2 )
{
    Vec4_Subtract( v1, v2, v1 );

    return fabs( Vec4_Get_Magnitude( v1 ) );
}


void Vec4_Set_Angle_Degs( vec4_t *v, float a )
{
    g_return_if_fail( v );

    a = Angle_To_Rad( a );

    *v[ 0 ] = cos( a );
    *v[ 1 ] = sin( a );
}


void Vec4_Set_Angle_Rads( vec4_t *v, float a )
{
    g_return_if_fail( v );

    *v[ 0 ] = cos( a );
    *v[ 1 ] = sin( a );
}


/*eof*/