#include "str_conversions.h"


uint8 Str_As_Int( char *s, int *out )
{
  int tmp = 0;
  
  if( sscanf( s, "%i", &tmp ) != 1 ) return FALSE;
  *out = tmp;
  return TRUE;
}


uint8 Str_As_Uint( char *s, uint32 *out )
{
  uint32 tmp = 0;
  
  if( sscanf( s, "%ui", &tmp ) != 1 ) return FALSE;
  *out = tmp;
  return TRUE;
}


uint8 Str_As_Float( char *s, float *out )
{
  float tmp = 0;
  
  if( sscanf( s, "%f", &tmp ) != 1 ) return FALSE;
  *out = tmp;
  return TRUE;
}


uint8 Str_As_Double( char *s, double *out )
{
  double tmp = 0;
  
  if( sscanf( s, "%lf", &tmp ) != 1 ) return FALSE;
  *out = tmp;
  return TRUE;
}


/* eof */