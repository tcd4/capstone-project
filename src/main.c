#include <stdlib.h>

#include "logger.h"
#include "parser.h"
#include "graphics2d.h"
#include "cmds.h"
#include "sprite.h"
#include "entity.h"
#include "level.h"


#define SYS_CONFIG	"../cfg/sys_config.def"


Level	*_level;


static uint8 			_game_over = 0;
static uint8 			_restart = 1;
static Dict			*_sys_config = NULL;
static SDL_GameController	*_controller;



static void	Init_Systems();
static void	Start_SDL();
static void	Start_Commands();
static void	Exit_Systems();
static void	Loop();
static void 	game_start();

void	restart( dataptr data );
void	game_over_func( dataptr data );


int main( int argc, const char *argv[] )
{ 
  while( _restart )
  {
    _restart = 0;
    _game_over = 0;
    
    Init_Systems();
    Loop();
    Exit_Systems();
  }
  
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
  
  if( SDL_NumJoysticks() > 0 )
  {
    _controller = SDL_GameControllerOpen( 0 );
    if( !_controller )
      Log( ERROR, "Unable to open controller. SDL Error: %s", SDL_GetError() );
  }
  
  Start_Commands();
  Init_2DGraphics( _sys_config );
  init_sprite_system();
  init_entity_system();
  
  Log( INFO, "All systems initialized." );
}


void Start_SDL()
{
  /*
  uint32 flags = 0;
  uint32 tmp = 0;
  */
  Log( INFO, "Initializing SDL" );
  /*
  Str_As_UInt( Find_In_Dict( _sys_config, "sdl_everything" ), &tmp );
  if( tmp )
  {
    Log( INFO, "SDL_INIT_EVERYTHING Flag Set" );
    flags |= SDL_INIT_EVERYTHING;
  }
  else
  {
  }
  */
  if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
  {
    Log( FATAL, "Unable to Initialize SDL" );
    exit( -1 );
  }
  
  Log( INFO, "SDL Initialized" );
}


void Start_Commands()
{
  init_cmd_system();

  if( !add_cmd( TRUE, "game_over", SDL_KEYUP, SDLK_ESCAPE, 0, game_over_func, NULL ) )
  {
    Log( FATAL, "game_over command wasn't added" );
    exit( -1 );
  }
  if( !add_cmd( TRUE, "restart", SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_START, 0, restart, NULL ) )
  {
    Log( FATAL, "restart command wasn't added" );
    exit( -1 );
  }
}


void Loop()
{
  SDL_Event event;
  
  game_start();
  
  while( !_game_over )
  {
    Clear_Frame();
    
    while( SDL_PollEvent( &event ) )
    {
      if( event.type == SDL_QUIT )
	_game_over = 1;
      else
	check_cmds( &event );
    }  
    
    update_all_entities();
    
    draw_level( _level );
    draw_all_entities();
    
    Next_Frame();
  }
}


void game_start()
{
  _level = load_level( "../cfg/level.def" );
  if( !_level )
  {
    Log( FATAL, "level didn't load" );
    exit( -1 );
  }
  
  Log( TRACE, "Game Started" ); 
}


void game_over_func( dataptr data )
{
  _game_over = 1;
}


void restart( dataptr data )
{
  _game_over = 1;
  _restart = 1;
}


void Exit_Systems()
{
  Log( INFO, "Shutting Down Systems!" );
  
  if( _controller )
    SDL_GameControllerClose( _controller );
  close_sprite_system();
  close_entity_system();
  free_level( &_level );
  close_cmd_system();
 /* Close_2DGraphics();*/
  /* close audio */
  Exit_Logging();
}


/* eof */