#ifndef __MY_TYPES__
#define __MY_TYPES__


/**
 * @file types.h
 * 
 * @brief contains types that I like to use
 */


#include <glib.h>


/* unsigned sized int defines */

typedef unsigned char uint8;             /**< unsigned 8 bit integer  */
typedef unsigned short uint16;           /**< unsigned 16 bit integer */
typedef unsigned int uint32;             /**< unsigned 32 bit integer */
typedef unsigned long uint64;            /**< unsigned 64 bit integer */

/* signed sized int defines */

typedef signed char int8;                /**< signed 8 bit integer  */
typedef signed short int16;              /**< signed 16 bit integer */
typedef signed int int32;                /**< signed 32 bit integer */
typedef signed long int64;               /**< signed 64 bit integer */


/* data pointer defines */

typedef void* dataptr;                   /**< void pointer data type */
typedef const void* constdataptr;        /**< constant void pointer data type */


/* TRUE/FALSE defines */

#ifndef FALSE
#define FALSE ( 0 )                      /**< false define */
#endif

#ifndef TRUE
#define TRUE (!FALSE)                    /**< true define */
#endif


/* function pointer defines */

typedef void ( *FreeNotify )( dataptr *data );                   /**< free function pointer */
typedef dataptr ( *CloneNotify )( dataptr data );                /**< duplicate function pointer */
typedef uint8 ( *CompareNotify )( dataptr d1, dataptr d2 );      /**< compare function pointer */


#endif