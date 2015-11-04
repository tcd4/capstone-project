#include "logger.h"

static FILE		*_log_file = NULL;
static uint8		flags = 0;
static GAsyncQueue	*_log_queue = NULL;
static SDL_Thread	*_logging_thread = NULL;

static int	_Logger_Thread_Func( dataptr data );
static void	_Write_Msg( char *msg );


void	Init_Logger( char *filename, uint8 threaded )
{
  if( Logger_Is_Init() )
  {
    Log( WARN, "Logger Is Already Initialized" );
    return;
  }
  
  flags |= LOGGER_INIT;
  flags &= ~LOGGER_DONE;
  
  _log_file = fopen( filename, "w" );
  if( !_log_file )
  {
    _log_file = stdout;
    Log( INFO, "Now Using stdout as the Log File" );
  }
  
  if( threaded )
  {
    Enable_Threaded_Logger();
  }
  
  Log( INFO, "Logger Initialized" );
}


uint8	Logger_Is_Init()
{
  if( flags & LOGGER_INIT ) return 1;
  return 0;
}


void	Enable_Threaded_Logger()
{
  if( Logger_Is_Threaded() )
  {
    Log( WARN, "Logger Is Already Threaded" );
    return;
  }
  
  _log_queue = g_async_queue_new();
  if( !_log_queue )
  {
    Log( ERROR, "Could not Allocate Memory for the Log Queue" );
    return;
  }
  
  _logging_thread = SDL_CreateThread( _Logger_Thread_Func, "logger", NULL );
  SDL_DetachThread( _logging_thread );
  
  flags |= LOGGER_THREADED;
  
  Log( INFO, "Logger Threading Enabled" );
}


uint8	Logger_Is_Threaded()
{
  if( flags & LOGGER_THREADED ) return 1;
  return 0;
}


char* Log_Level_To_Str( Log_Level lev )
{
  char *l;
  
  l = g_new0( char, 5 );
  
  switch( lev )
  {    
    case 1:
      l = "FATAL";
      break;
      
    case 2:
      l = "ERROR";
      break;
      
    case 4:
      l = "WARN";
      break;
      
    case 8:
      l = "TRACE";
      break;
      
    case 16:
      l = "INFO";
      break;
      
    case 31:
      l = "ALL";
      break;
      
    default:
      l = "NONE";
      break;
  }
  
  return l;
}


void	Log_Msg( char *file, int line, Log_Level lvl, char *msg, ... )
{
  char *b, *m, *l;
  va_list ap;
  
  if( !Logger_Is_Init() ) return;
  
  va_start( ap, msg );
  g_vasprintf( &b, msg, ap );
  va_end( ap );
  
  l = Log_Level_To_Str( lvl );
  m = g_strdup_printf( "%s:%i --- %s --- %s", file, line, l, b );
  
  if( Logger_Is_Threaded() )
    g_async_queue_push( _log_queue, m );
  else
    _Write_Msg( m );
}


void	_Write_Msg( char *msg )
{
  fprintf( _log_file, "%s\n", msg );
  printf( "%s\n", msg );
  
  fflush( _log_file );
  g_free( msg );
}


void	Exit_Logging()
{
  flags &= ~LOGGER_INIT;
  
  if( Logger_Is_Threaded() )
  {
    flags |= LOGGER_DONE;
    return;
  }
  else
  {
    Log( INFO, "Logging Complete" );
    
    if( _log_file != stdout )
      fclose( _log_file );
  }
}


int	_Logger_Thread_Func( dataptr data )
{
  char *msg = NULL;
  
  while( !( flags & LOGGER_DONE ) || ( msg != NULL ) )
  {
    msg = ( char * )g_async_queue_pop( _log_queue );
    if( msg )
    {
      _Write_Msg( msg );
    }
  }
  
  flags &= ~LOGGER_THREADED;
  Exit_Logging();
  
  return 0;
}



/*eof*/