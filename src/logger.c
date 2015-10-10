#include "logger.h"

statie FILE		*_log_file = NULL;
static uint8		flags = 0;
static GAsyncQueue	*_log_queue = NULL;
static SDL_Thread	*_logging_thread = NULL;

static int	_Logger_Thread_Func( dataptr data );
static void	_Write_Msg( char *msg );


void	Init_Logger( char *filename, uint8 threaded )
{
  if( Logger_Is_Init() )
  {
    /* log msg */
    return;
  }
  
  _log_file = fopen( filename, "w" );
  if( !_log_file )
  {
    _log_file = stdout;
    /* log msg */
  }
  
  if( threaded )
  {
    Enable_Threaded_Logger();
  }
  
  flags |= LOGGER_INIT;
  /* log msg */
}


uint8	Logger_Is_Init()
{
  if( flags & LOGGER_INIT ) return 1;
  return 0;
}


void	Enable_Threaded_Logger()
{
  _log_queue = g_async_queue_new();
  if( !_log_queue )
  {
    /* log msg */
    return;
  }
  
  _logging_thread = SDL_CreateThread( _Logger_Thread_Func, "logger", NULL );
  SDL_DetachThread( _logging_thread );
  
  flags |= LOGGER_THREADED;
  /* log msg */
}


/*eof*/