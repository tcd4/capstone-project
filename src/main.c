#include <stdlib.h>

#include "logger.h"


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
  Init_Logger( "logs.txt", 1 );
}


void Loop()
{
}


void Exit_Systems()
{
  Exit_Logging();
}