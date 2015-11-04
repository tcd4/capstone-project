#include <stdlib.h>

#include "logger.h"
#include "parser.h"
#include "graphics2d.h"
#include "cmds.h"
#include "sprite.h"
#include "entity.h"


#define SYS_CONFIG	"../cfg/sys_config.def"


static uint8 	_game_over = 0;
static Dict	*_sys_config = NULL;


static void	Init_Systems();
static void	Start_SDL();
static void	Start_Commands();
static void	Exit_Systems();
static void	Loop();

void	game_over_func( dataptr data );


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
  Start_Commands();
  Init_2DGraphics( _sys_config );
  init_sprite_system();
  init_entity_system();
  
  Log( INFO, "All systems initialized." );
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


void Start_Commands()
{
  init_cmd_system();
  if( !add_cmd( TRUE, "game_over", SDLK_ESCAPE, 0, game_over_func, NULL ) )
  {
    Log( FATAL, "game_over command wasn't added" );
    exit( -1 );
  }
}


void Loop()
{
  SDL_Event event;
  Sprite *test;
  vec2_t p, s;
  
  Vec2_Set( p, 20, 20 );
  Vec2_Clear( s );
  
  test = load_sprite_from_config( "../cfg/test_sprite.def" );
  
  while( !_game_over )
  {
    while( SDL_PollEvent( &event ) )
    {
      if( event.type == SDL_QUIT )
      {
	_game_over = 1;
      }
      else if( event.type == SDL_KEYDOWN )
      {
	check_cmds( &event );
      }
      
      update_all_entities();
      draw_all_entities();
      
      draw_sprite( test, p, s, s, 0 );
      
      Next_Frame();
    }
  }
}


void game_over_func( dataptr data )
{
  _game_over = 1;
}


void Exit_Systems()
{
  Log( INFO, "Shutting Down Systems!" );
  close_cmd_system();
  close_sprite_system();
  close_entity_system();
  Close_2DGraphics();
  /* close audio */
  SDL_Quit();
  Exit_Logging();
}