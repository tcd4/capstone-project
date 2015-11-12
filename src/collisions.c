#include "collisions.h"


uint8 rect_rect_collision( vec2_t s1, vec2_t p1, vec2_t s2, vec2_t p2 )
{
  if( ( p1[ XA ] > p2[ XA ] + s2[ XA ] ) || ( p2[ XA ] > p1[ XA ] + s1[ XA ] ) ||
      ( p1[ YA ] > p2[ YA ] + s2[ YA ] ) || ( p2[ YA ] > p1[ YA ] + s1[ YA ] ) )
    return FALSE;
  
  return TRUE;
}


/* eof */