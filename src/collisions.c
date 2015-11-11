#include "collisions.h"


uint8 rect_rect_collision( vec2_t s1, vec2_t p1, vec2_t s2, vec2_t p2 )
{
  if( ( p1[ 0 ] > p2[ 0 ] + s2[ 0 ] ) || ( p2[ 0 ] > p1[ 0 ] + s1[ 0 ] ) ||
      ( p1[ 1 ] > p2[ 1 ] + s2[ 1 ] ) || ( p2[ 1 ] > p1[ 1 ] + s1[ 1 ] ) )
    return FALSE;
  
  return TRUE;
}


/* eof */