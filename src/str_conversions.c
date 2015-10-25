#include "str_conversions.h"


uint8 Str_As_Int( char *s, int *out )
{
  int tmp = 0;
  
  if( !s || !out ) return FALSE; 
  
  if( sscanf( s, "%i", &tmp ) != 1 ) return FALSE;
  *out = tmp;
  return TRUE;
}


uint8 Str_As_UInt( char *s, uint32 *out )
{
  uint32 tmp = 0;
  
  if( !s || !out ) return FALSE; 
  
  if( sscanf( s, "%ui", &tmp ) != 1 ) return FALSE;
  *out = tmp;
  return TRUE;
}


uint8 Str_As_Float( char *s, float *out )
{
  float tmp = 0;
  
  if( !s || !out ) return FALSE; 
  
  if( sscanf( s, "%f", &tmp ) != 1 ) return FALSE;
  *out = tmp;
  return TRUE;
}


uint8 Str_As_Double( char *s, double *out )
{
  double tmp = 0;
  
  if( !s || !out ) return FALSE; 
  
  if( sscanf( s, "%lf", &tmp ) != 1 ) return FALSE;
  *out = tmp;
  return TRUE;
}


uint8 Str_As_Vec2( char *s, vec2_t *out )
{
  vec2_t tmp;
  
  if( !s || !out ) return FALSE; 
  
  Vec2_Clear( tmp );
  
  if( sscanf( s, "%lf,%lf", &tmp[ 0 ], &tmp[ 1 ] ) != 2 ) return FALSE;
  Vec2_Copy( tmp, *out );
  return TRUE;
}


uint8 Str_As_Vec3( char *s, vec3_t *out )
{
  vec3_t tmp;
  
  if( !s || !out ) return FALSE; 
  
  Vec3_Clear( tmp );
  
  if( sscanf( s, "%lf,%lf,%lf", &tmp[ 0 ], &tmp[ 1 ], &tmp[ 2 ] ) != 3 ) return FALSE;
  Vec3_Copy( tmp, *out );
  return TRUE;
}


uint8 Str_As_Vec4( char *s, vec4_t *out )
{
  vec4_t tmp;
  
  if( !s || !out ) return FALSE; 
  
  Vec4_Clear( tmp );
  
  if( sscanf( s, "%lf,%lf,%lf,%lf", &tmp[ 0 ], &tmp[ 1 ], &tmp[ 2 ], &tmp[ 3 ] ) != 4 ) return FALSE;
  Vec4_Copy( tmp, *out );
  return TRUE;
}


/* eof */