#include "cmds.h"


static GSList		*_cmd_list = NULL;	/**< the linked list of commands */
static GSList		*_cmd_list_iter = NULL;	/**< an iterator for _cmd_list */


static Cmd*	_find_cmd_by_name( char *name );	/**< finds a command in the command list */
static void	_cmd_hit( Cmd *cmd );			/**< updates the command info when the command is activated */


void init_cmd_system()
{
  if( cmd_system_is_init() ) return;
  
  _cmd_list = g_slist_alloc();
 if( !_cmd_list )
 {
   Log( FATAL, "Command System Could not be Initialized" );
   exit( -1 );
 }
 _cmd_list->data = NULL;
}


uint8 cmd_system_is_init()
{
  if( !_cmd_list ) return FALSE;
  return TRUE;
}


Cmd* _find_cmd_by_name( char *name )
{
  Cmd *tmp;
  
  _cmd_list_iter = _cmd_list->next;
  
  while( _cmd_list_iter )
  {
    tmp = ( Cmd* )_cmd_list_iter->data;
    
    if( !strcmp( tmp->name, name ) ) return tmp;
    
    _cmd_list_iter = _cmd_list_iter->next;
  }
  
  return NULL;
}


uint8 add_cmd( uint8 on, char *name, uint32 type, int id, uint32 hold, EventNotify event, dataptr param )
{
  Cmd *new = NULL;
  
  if( !cmd_system_is_init() ) return FALSE;
  if( !name ) return FALSE;
  
  new = g_new0( Cmd, 1 );
  if( !new ) return FALSE;
  
  if( !g_slist_append( _cmd_list, new ) )
  {
    free( new );
    return FALSE;
  }
  
  new->name = strdup( name );
  new->type = type;
  new->id = id;
  new->hold_time = hold;
  new->event = event;
  new->event_param = param;
  new->inuse = on;
  
  Log( TRACE, "%s command added, using key %i", new->name, new->id );
  
  return TRUE;
}


void turn_on_cmd( char *name )
{
  Cmd *tmp;
  
  tmp = _find_cmd_by_name( name );
  if( !tmp ) return;
  tmp->inuse = 1;
}


void turn_off_cmd( char *name )
{
  Cmd *tmp;
  
  tmp = _find_cmd_by_name( name );
  if( !tmp ) return;
  tmp->inuse = 0;
}


void remove_cmd_by_name( char *name )
{
  Cmd *tmp;
  
  tmp = _find_cmd_by_name( name );
  if( !tmp ) return;
  
  g_slist_delete_link( _cmd_list, g_slist_find( _cmd_list, tmp ) );
  free( tmp->name );
  free( tmp );
}


void close_cmd_system()
{
  Cmd *tmp;
  
  _cmd_list_iter = _cmd_list->next;
  g_slist_delete_link( _cmd_list, _cmd_list );
  _cmd_list = NULL;
  
  while( _cmd_list_iter )
  {
    tmp = ( Cmd* )_cmd_list_iter->data;
    free( tmp->name );
    free( tmp );
    _cmd_list_iter = g_slist_delete_link( _cmd_list_iter, _cmd_list_iter );
  }
}


void check_cmds( SDL_Event *event )
{
  if( !event ) return;
  
  _cmd_list_iter = _cmd_list->next;
  
  while( _cmd_list_iter )
  {
    check_cmd( event, _cmd_list_iter->data );
    _cmd_list_iter = _cmd_list_iter->next;
  }
}


void check_cmd( SDL_Event *event, Cmd *cmd )
{
  if( !event || !cmd || !cmd->inuse || ( cmd->type != event->type ) ) return;

  if( event->type == SDL_KEYDOWN || event->type == SDL_KEYUP )
  {
    if( event->key.keysym.sym == cmd->id )
      _cmd_hit( cmd );
  }
  else if( event->type == SDL_JOYBUTTONDOWN || event->type == SDL_JOYBUTTONUP )
  {
    if( event->jbutton.button == cmd->id )
      _cmd_hit( cmd );
  }
  else if( event->type == SDL_CONTROLLERBUTTONDOWN || event->type == SDL_CONTROLLERBUTTONUP )
  {
    if( event->cbutton.button == cmd->id )
      _cmd_hit( cmd );
  }
}


void _cmd_hit( Cmd *cmd )
{
  if( cmd->hold_time )
  {
    if( cmd->time_pressed > cmd->hold_time )
    {
      cmd->start_time = 0;
      cmd->time_pressed = 0;
      cmd->event( cmd->event_param );
    }
    else if( !cmd->start_time )
    {
      cmd->start_time = Get_Time();
    }
    else
    {
      cmd->time_pressed = Get_Time() - cmd->start_time;
    }
  }
  else
  {
    cmd->event( cmd->event_param );
  }
}


/* eof */