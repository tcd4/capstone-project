#ifndef __DEF_PARSER__
#define __DEF_PARSER__



#include <yaml.h>

#include "dict.h"


/**
 * @brief parses a file
 * 
 * @param filename	the file to parse
 * 
 * @return a Dict containing the parsed values or NULL on error
 */
Dict*	Parse( char *filename );


#endif