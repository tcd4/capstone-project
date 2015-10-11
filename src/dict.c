#include "dict.h"


Dict*	New_Dict()
{
  Dict *new;
  
  new = g_new0( Dict, 1 );
  if( !new ) return NULL;
  
  new->table =  g_hash_table_new_full( g_str_hash, g_str_equal, g_free, g_free );
  if( !new->table ) return NULL;
  
  return new;
}


Dict*	Add_To_Dict( Dict *d, char *key, char *val )
{
  char *k, *v;
  
  k = strdup( key );
  v = strdup( val );
  
  if( g_hash_table_lookup( d->table, k ) || !g_hash_table_insert( d->table, k, v ) )
  {
    g_free( k );
    g_free( v );
    
    return NULL;
  }
  
  d->length++;
  
  return d;
}


char*	Find_In_Dict( Dict *d, char *key )
{
  if( !d ) return NULL;
  
  return g_hash_table_lookup( d->table, key );
}


void	Free_Dict( Dict **d )
{
  Dict *t;
  
  if( !d ) return;
  
  t = *d;
  
  if( !t ) return;
  
  g_hash_table_destroy( t->table );
  
  free( t );
  *d = NULL;
}


/*eof*/