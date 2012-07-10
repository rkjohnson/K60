//-----------------------------------------------------------------------------
/*
Copyright (c) 2012 JAR
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 * @file MAIN_TASK.H
 *
 * application, board, and task setup. Main program loop
 *
 * @version $Id$
 */
//-----------------------------------------------------------------------------

#ifndef _MAIN_TASK_H_
#define _MAIN_TASK_H_

/* #####   HEADER FILE INCLUDES   ################################################### */
#include <mqx.h>
#include <bsp.h>
#include <shell.h>
#include <rtcs.h>
#include <sh_rtcs.h>
#include <ipcfg.h>

/* #####   EXPORTED MACROS   ######################################################## */
#define APPLICATION_HAS_SHELL

#define MAIN_TASK       1
#define ENET_DEVICE     0
#define RTCS_DHCP       1

#define ENET_IPADDR     IPADDR(169,254,3,3)
#define ENET_IPMASK     IPADDR(255,255,0,0)
#define ENET_GATEWAY    IPADDR(0,0,0,0)
#define RTCS_PPP        0

/* PPP device must be set manually and
** must be different from the default IO channel (BSP_DEFAULT_IO_CHANNEL)
*/
#define PPP_DEVICE      "ittyb:"

/*
** Define PPP_DEVICE_DUN only when using PPP to communicate
** to Win9x Dial-Up Networking over a null-modem
** This is ignored if PPP_DEVICE is not #define'd
*/
#define PPP_DEVICE_DUN  1

/*
** Define the local and remote IP addresses for the PPP link
** These are ignored if PPP_DEVICE is not #define'd
*/
#define PPP_LOCADDR     IPADDR(192,168,0,216)
#define PPP_PEERADDR    IPADDR(192,168,0,217)

/*
** Define a default gateway
*/
#define GATE_ADDR       IPADDR(192,168,0,1)

/* #####   EXPORTED TYPE DEFINITIONS   ############################################## */

/* #####   EXPORTED DATA TYPES   #################################################### */

/* #####   EXPORTED VARIABLES   ##################################################### */
extern boolean bPrintAccelData;

/* #####   EXPORTED FUNCTION DECLARATIONS   ######################################### */
void main_task( uint_32 );
void rtcs_init( void );

#endif /* _MAIN_TASK_H_ */
