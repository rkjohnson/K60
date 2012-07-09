//-----------------------------------------------------------------------------
/*
Copyright (c) 2012 JAR
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 * @file TOWER_IO.H
 *
 * functions for setting up & interfacing with the tower's IO
 *
 * @version $Id$
 */
//-----------------------------------------------------------------------------

#ifndef _TOWER_IO_H_
#define _TOWER_IO_H_

/* #####   HEADER FILE INCLUDES   ################################################### */

/* #####   EXPORTED MACROS   ######################################################## */

/* #####   EXPORTED TYPE DEFINITIONS   ############################################## */
typedef enum {
   LED1 = 0,
   LED2,
   LED3,
   LED4,
   MAX_OUTPUTS
} Output_t;

typedef enum {
   SW1_INPUT = 0,
   SW2_INPUT,
   MAX_INPUTS
} Input_t;

/* #####   EXPORTED DATA TYPES   #################################################### */

/* #####   EXPORTED VARIABLES   ##################################################### */

/* #####   EXPORTED FUNCTION DECLARATIONS   ######################################### */
boolean initialize_io( void );
boolean get_input( Input_t );
void set_output( Output_t, boolean );
void reset_outputs( void );


#endif /* _TOWER_IO_H_ */
