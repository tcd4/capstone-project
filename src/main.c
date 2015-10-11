#include <stdlib.h>

#include "logger.h"
#include "parser.h"


#define SYS_CONFIG	"../cfg/sys_config.def"


uint8 			game_over = 0;
static Dict	*_sys_config = NULL;


static void	Init_Systems();
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
  char *log_file;
  
  _sys_config = Parse( "../cfg/sys_config.def" );
  if( !_sys_config )
    printf( "fuck\n" );
  
  log_file = Find_In_Dict( _sys_config, "log_file" );
  printf( "log file: %s\n", log_file );
  
  Init_Logger( "logs.txt", 0 );
}


void Loop()
{
}


void Exit_Systems()
{
  Exit_Logging();
}