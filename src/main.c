#include <stdlib.h>


uint8 game_over = 0;

static void Init_Systems();
static void Exit_Systems();
static void Loop();


int main( int argc, const char *argv[] )
{
  atexit( Exit_Systems );
  
  Init_Systems();
  Loop();
  
  exit( 0 );
  return 0;
}


void Init_Systems()
{
}


void Loop()
{
}


void Exit_Systems()
{
}