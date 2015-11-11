#include "physics.h"

struct space_s
{
  GSList	bodies;		/**< a list of bodies in the space */
  uint8		steps;		/**< the number of steps the space should perform per frame */
  double	step_factor;	/**< how much physics is scaled down per step */
};


Space* create_space( uint8 steps )
{
  Space *new;
  
  Log( INFO, "Creating space." );
  
  new = g_new0( Space, 1 );
  if( !new )
  {
    Log( WARN, "Failed to create space." );
    return NULL;
  }
  
  Log( INFO, "Space created." );
  
  return new;
}


/* eof */