//-----------------------------------------------------------------------------
/*
Copyright (c) 2012 JAR
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 * @file MAIN_TASK.C
 *
 * application, board, and task setup. Main program loop
 *
 * @version $Id$
 */
//-----------------------------------------------------------------------------

/* #####   HEADER FILE INCLUDES   ################################################### */
#include "main.h"
#include "demo.h"

/* #####   VARIABLES  -  EXPORTED VARIABLES   ####################################### */
SENSOR_DATA Sensor;

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ################################### */

/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ######################### */

/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ################################ */
const SHELL_COMMAND_STRUCT Shell_commands[] = {

   /* RTCS commands */
   { "arpadd",    Shell_arpadd },
   { "arpdel",    Shell_arpdel },
   { "arpdisp",   Shell_arpdisp },
   { "gate",      Shell_gate },
   { "gethbn",    Shell_get_host_by_name },
   { "getrt",     Shell_getroute },
   { "ipconfig",  Shell_ipconfig },
   { "netstat",   Shell_netstat },
#if RTCSCFG_ENABLE_ICMP
   { "ping",      Shell_ping },
#endif
   { "telnet",    Shell_Telnet_client },
   { "telnetd",   Shell_Telnetd },
   { "walkrt",    Shell_walkroute },

/*    Add your custom shell commands here    */
/* { "command_name",        Your_function }, */
   { "sh",        Shell_sh },
   { "help",      Shell_help },
   { "?",         Shell_command_list },
   { "exit",      Shell_exit },
   { "led",       Shell_led },
   { NULL,        NULL },
};

#if 0
const SHELL_COMMAND_STRUCT Telnetd_shell_commands[] = {
   /* RTCS commands */
   { "exit",      Shell_exit },
   { "gethbn",    Shell_get_host_by_name },
   { "getrt",     Shell_getroute },
   { "help",      Shell_help },
   { "ipconfig",  Shell_ipconfig },
   { "netstat",   Shell_netstat },
   { "pause",     Shell_pause },
#if RTCSCFG_ENABLE_ICMP
   { "ping",      Shell_ping },
#endif
   { "telnet",    Shell_Telnet_client },
   { "walkrt",    Shell_walkroute },
   { "?",         Shell_command_list },
   { NULL,        NULL }
};
#endif

/*
 * Application task list
 */
TASK_TEMPLATE_STRUCT MQX_template_list[] =
{
/*  Task number, Entry point, Stack, Pri, String,  Auto? */
    {MAIN_TASK,   main_task,   2000,  10,  "main",  MQX_AUTO_START_TASK},
    {ADC_TASK,    ADC_Task,    2000,  8,   "ADC",   0,                 },
    {ACCEL_TASK,  accel_task,  2000,  9,   "accel", 0,                 },
    {0,           0,           0,     0,   0,       0,                 }
};

/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ############################### */

/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ############################ */

// ===  FUNCTION  ======================================================================
//         Name:  main_task
/**
 * @brief sets up the board & RCTS. Launches tasks and runs the shell
 *
 * @param uint_32 initial_data
 * 
 * @return void
 */
// =====================================================================================
void main_task ( uint_32 initial_data )
{
   MQX_FILE_PTR serial_fd;
   int i;
   uint_32 flags = 0;

   /* open the serial port */
   /*
     * Other Serial console options:(do not forget to enable BSPCFG_ENABLE_TTY define if changed)
     *      "ittyf:"     OSJTAG-COM  interrupt mode
     *      "ttyd:"      TWR-SER     polled mode
     *      "ittyd:"     TWR-SER     interrupt mode
     *      "iodebug:"   IDE debug console
     */
//   serial_fd = fopen("ttyd:", 0);
//   ioctl(serial_fd, IO_IOCTL_SERIAL_SET_FLAGS, &flags);
//   
//   for( i = 0; i < 1000; i++ ) {
//    fprintf(serial_fd,".");
//   }
//   
//   fprintf(serial_fd,"\r\nHELLO!!!\r\n");
//   fprintf(serial_fd,"Starting system...\r\n");
//   printf("Hello\r\n");
//
   /* Setup GPIO */
   initialize_io();
   
   /* Create Acceletometer Task to read accelerometer data */
   _task_create(0,ACCEL_TASK,0);

   /* Create ADC Task to read POT and Temp Sensor */
   _task_create(0,ADC_TASK,0);
   
   /* RTCS init */
   rtcs_init();

   for (;;) {
      /* Run the shell */
      printf("starting");
      Shell(Shell_commands, NULL);
      printf("Shell exited, restarting...\n");
   }
}    /* -----  end of function main_task  ----- */

/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ##################### */
// ===  FUNCTION  ======================================================================
//         Name:  Shell_led
/**
 * @brief handler for the led shell command
 *
 * @param void
 * 
 * @return void
 */
// =====================================================================================
void Shell_led ( void )
{
   
   return ;
}      /* -----  end of function Shell_led  ----- */

/* EOF */
