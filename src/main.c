#include <stdlib.h>

#include "logger.h"
#include "parser.h"
#include "graphics2d.h"


#define SYS_CONFIG	"../cfg/sys_config.def"


uint8 		game_over = 0;
static Dict	*_sys_config = NULL;


static void	Init_Systems();
static void	Start_SDL();
static void	Exit_Systems();
static void	Loop();


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
  _sys_config = Parse( "../cfg/sys_config.def" );
  if( !_sys_config )
    printf( "fuck\n" );
  
  Init_Logger( Find_In_Dict( _sys_config, "log_file" ), 0 );
  Start_SDL();
  Init_2DGraphics( _sys_config );
}


void Start_SDL()
{
  uint32 flags = 0;
  uint32 tmp = 0;
  
  Log( INFO, "Initializing SDL" );
  
  Str_As_UInt( Find_In_Dict( _sys_config, "sdl_everything" ), &tmp );
  if( tmp )
  {
    Log( INFO, "SDL_INIT_EVERYTHING Flag Set" );
    flags |= SDL_INIT_EVERYTHING;
  }
  else
  {
  }
  
  if( SDL_Init( flags ) != 0 )
  {
    Log( FATAL, "Unable to Initialize SDL" );
    exit( -1 );
  }
  
  Log( INFO, "SDL Initialized" );
}


void Loop()
{
}


void Exit_Systems()
{
  Log( INFO, "Shutting Down Systems!" );
  SDL_Quit();
  Exit_Logging();
}