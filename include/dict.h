#ifndef __DICT__
#define __DICT__


/**
 * @file dict.h
 * 
 * @brief a dictionary data type
 */


#include <glib.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"

typedef struct dict_s
{
  GHashTable	*table;
  uint32	length;
}Dict;


/**
 * @brief creates a new Dict
 * 
 * @return a pointer to the new Dict
 */
Dict*	New_Dict();

/**
 * @brief adds an item to a Dict
 * 
 * @param d	the Dict to add to
 * @param key	the key to add
 * @param val	the value of the key
 * 
 * @return d or NULL on error
 */
Dict*	Add_To_Dict( Dict *d, char *key, char *val );

/**
 * @brief finds a value in a Dict from a key
 * 
 * @param d	the Dict to search in
 * @param key	the key to search for
 * 
 * @return the value found or NULL if not found
 */
char*	Find_In_Dict( Dict *d, char *key );


/**
 * @brief frees a Dict
 * 
 * @param d	a pointer to a pointer to the Dict to free
 */
void	Free_Dict( Dict **d );


#endif