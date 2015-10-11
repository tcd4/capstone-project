#include "parser.h"


static void _Parse( yaml_parser_t *parser, Dict *d );


Dict*	Parse( char *filename )
{
  Dict		*parsed;
  FILE		*f;
  yaml_parser_t	parser;
  
  if( !yaml_parser_initialize( &parser ) ) return NULL;

  f = fopen( filename, "r" );
  if( !f ) return NULL;
  
  parsed = New_Dict();  
  if( !parsed ) return NULL;
  
  yaml_parser_set_input_file( &parser, f );
  
  _Parse( &parser, parsed );
  
  yaml_parser_delete( &parser );
  fclose( f );
  
  return parsed;
}


static void _Parse( yaml_parser_t *parser, Dict *d )
{
  int		done = 0;
  int		state = 0;
  char		key[ 128 ];
  yaml_event_t	event;
  
  strncpy( key, "", 128 );
  
  do
  {
    yaml_parser_parse( parser, &event );
    
    switch( event.type )
    {
      case YAML_SCALAR_EVENT:
	if( state == 0 )
	  strncpy( key, ( char* )event.data.scalar.value, 128 );
	else
	  Add_To_Dict( d, key, ( char* )event.data.scalar.value );
	  
	state ^= 1;
	break;
	
      case YAML_SEQUENCE_START_EVENT:
	break;
	
      case YAML_MAPPING_START_EVENT:
	break;
	
      case YAML_MAPPING_END_EVENT:
	break;
	
      case YAML_STREAM_END_EVENT:
	done = 1;
	break;
	
      case YAML_SEQUENCE_END_EVENT:
	done = 1;
	break;
	
      default:
	break;
    }
    
    if( parser->error != YAML_NO_ERROR ) return;
    
    yaml_event_delete( &event );
  }
  while( !done );
}


/*eof*/