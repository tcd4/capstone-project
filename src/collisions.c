#include "collisions.h"
#include "logger.h"

uint8 rect_rect_collision( vec2_t s1, vec2_t p1, vec2_t s2, vec2_t p2 )
{
  /*Log( TRACE, "x1: %lf, y1: %lf, x2: %lf, y2: %lf", p1[ XA ], p1[ YA ], p2[ XA ], p2[ YA ] );*/
  if( ( p1[ XA ] > p2[ XA ] + s2[ XA ] ) || ( p2[ XA ] > p1[ XA ] + s1[ XA ] ) ||
      ( p1[ YA ] > p2[ YA ] + s2[ YA ] ) || ( p2[ YA ] > p1[ YA ] + s1[ YA ] ) )
    return FALSE;
  
  return TRUE;
}


/* eof */