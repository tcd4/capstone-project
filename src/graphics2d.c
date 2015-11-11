#include "graphics2d.h"
#include <SDL.h>


static uint32	_frame_delay;		/**< the delay between frames */
static uint32	_current_time;		/**< the current runtime of the program */
static uint32	_current_frame = 0;	/**< the current frame */
static uint32	_previous_time = 0;	/**< the time of the previous frame */
static uint32	_delay_diff;		/**< the difference between current_time and previous time */

static vec2_t		_resolution;		/**< the resolution of the screen */
static vec2_t		_render_resolution;	/**< the renderer's resolution */
static SDL_Window	*_main_window = NULL;	/**< the main window */
static SDL_Renderer	*_renderer = NULL;	/**< the graphics renderer */
static SDL_Texture	*_texture = NULL;	/**< the screen texture */
static SDL_Surface	*_surface = NULL;	/**< the screen surface */

static uint32	_bpp;		/**< the bits-per-pixel */
static uint32	_rmask;		/**< the red mask */
static uint32	_gmask;		/**< the green mask */
static uint32	_bmask;		/**< the blue mask */
static uint32	_amask;		/**< the alpha mask */

static uint32	_background_color = 0;	/**< the background color of the main window */
static vec4_t	_background_color_v;	/**< the background color of the main window as a vec4_t */


void Init_2DGraphics( Dict *config )
{
  int flags = 0;
  int tmp = 0;
  
  if( !config )
  {
    Log( FATAL, "No config to initialize graphics system" );
    exit( -1 );
  }
  
  Log( INFO, "Initializing Graphics" );
  
  Vec2_Clear( _resolution );
  Vec2_Clear( _render_resolution );
  Vec4_Clear( _background_color_v );
  Vec4_Set( _background_color_v, 255, 255, 255, 255 );
  Vec2_Set( _resolution, 1920, 1080 );
  Vec2_Set( _render_resolution, 1920, 1080 );
  
  /* set config stuff */
  /*
  Str_As_Vec2( Find_In_Dict( config, "resolution" ), &_resolution );
  Str_As_Vec2( Find_In_Dict( config, "render_resolution" ), &_render_resolution );
  */
  
  Str_As_UInt( Find_In_Dict( config, "bpp" ), &_bpp );
  Str_As_UInt( Find_In_Dict( config, "frame_delay" ), &_frame_delay );
  /*
  Str_As_Vec4( Find_In_Dict( config, "background_color" ), &_background_color_v );
  */
  Str_As_Int( Find_In_Dict( config, "fullscreen" ), &tmp );
  if( tmp )
    flags |= SDL_WINDOW_FULLSCREEN;
  Str_As_Int( Find_In_Dict( config, "borderless" ), &tmp );
  if( tmp )
    flags |= SDL_WINDOW_BORDERLESS;
  
  _main_window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _resolution[ 0 ], _resolution[ 1 ], flags );
  if( !_main_window )
  {
    Log( FATAL, "Failed to Create the Main Window" );
    exit( -1 );
  }
  
  _renderer = SDL_CreateRenderer( _main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE );
  if( !_renderer )
  {
    Log( FATAL, "Failed to Create the Renderer" );
    exit( -1 );
  }
  
  SDL_SetRenderDrawColor( _renderer, 0, 0, 0, 255 );
  SDL_RenderClear( _renderer );
  SDL_RenderPresent( _renderer );
  SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "linear" );
  SDL_RenderSetLogicalSize( _renderer, _render_resolution[ 0 ], _render_resolution[ 1 ] );
  
  SDL_PixelFormatEnumToMasks( SDL_PIXELFORMAT_RGBA8888, ( int* )&_bpp, &_rmask, &_gmask, &_bmask, &_amask );
  
  _surface = SDL_CreateRGBSurface( 0, _render_resolution[ 0 ], _render_resolution[ 1 ], _bpp, _rmask, _gmask, _bmask, _amask );
  if( !_surface )
  {
    Log( FATAL, "Failed to Create the Screen Surface" );
    exit( -1 );
  }
  
  _texture = SDL_CreateTexture( _renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, _render_resolution[ 0 ], _render_resolution[ 1 ] );
  if( !_texture )
  {
    Log( FATAL, "Failed to Create the Screen Texture due to: %s", SDL_GetError() );
    exit( -1 );
  }
  
  _background_color = SDL_MapRGB( _surface->format, _background_color_v[ 0 ], _background_color_v[ 1 ], _background_color_v[ 2 ] );

  /* init camera */
  /* init mouse  */
  
  _current_time = SDL_GetTicks();
  
  Log( INFO, "Graphics Initialized" );
}


void Next_Frame()
{  
  SDL_RenderPresent( _renderer );
  
  /* delay the frame */
  _previous_time = _current_time;
  _current_time = SDL_GetTicks();
  _delay_diff = _current_time - _previous_time;
  
  if( _delay_diff < _frame_delay )
    SDL_Delay( _frame_delay - _delay_diff );
}


SDL_Surface* Get_Screen()
{
  return _surface;
}


SDL_Renderer* Get_Renderer()
{
  return _renderer;
}


uint32 Get_Time()
{
  return _current_time;
}


uint32 Get_Frame()
{
  return _current_frame;
}


vec2_t* Get_Resolution()
{
  return &_resolution;
}


void Close_2DGraphics()
{
  Log( INFO, "Closing Graphics" );
  
  if( _texture )
  {
    SDL_DestroyTexture( _texture );
    _texture = NULL;
  }
  
  if( _renderer )
  {
    SDL_DestroyRenderer( _renderer );
    _renderer = NULL;
  }
  
  if( _main_window )
  {
    SDL_DestroyWindow( _main_window );
    _main_window = NULL;
  }
  
  if( _surface )
  {
    SDL_FreeSurface( _surface );
    _surface = NULL;
  }
  
  Log( INFO, "Graphics Closed" );
}

/*eof*/