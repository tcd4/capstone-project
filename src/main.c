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
static void 	game_start();

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
    draw_all_entities();
    
    Next_Frame();
  }
}


void game_start()
{
  Entity *new;
  vec2_t s,p;
  
  new = create_entity();
  if( !new )
  {
    Log( FATAL, "fuck" );
    exit( -1 );
  }
  
  add_draw_state( new, "../cfg/test_actor.def", NULL );
  new->draw_state = 0;
  new->visible = 1;
  
  Vec2_Set( s, 50, 50 );
  Vec2_Set( p, 1000, 500 );
  new->body = create_body( new, 1, s, p, NULL );
  Vec2_Set( new->body->velocity, 10, 0 );
  Vec2_Set( new->body->acceleration, -0.1, 0 );
  add_ent_to_space( new );
  
  Log( TRACE, "Game Started" ); 
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


/* eof */