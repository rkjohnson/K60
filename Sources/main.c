/**HEADER*******************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 1989-2008 ARC International;
* All Rights Reserved
*
**************************************************************************** 
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************
*
* Comments:
*
*   This file contains main initialization for your application
*   and infinite loop
*
*END************************************************************************/

#include "main.h"



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
   { NULL,        NULL },
};

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


TASK_TEMPLATE_STRUCT MQX_template_list[] =
{
/*  Task number, Entry point, Stack, Pri, String, Auto? */
   {MAIN_TASK,   Main_task,   2000,  9,   "main", MQX_AUTO_START_TASK},
   {0,           0,           0,     0,   0,      0,                 }
};

/*TASK*-----------------------------------------------------------------
*
* Function Name  : Main_task
* Comments       :
*    This task initializes MFS and starts SHELL.
*
*END------------------------------------------------------------------*/

void Main_task(uint_32 initial_data)
{
	MQX_FILE_PTR serial_fd;
	int i;
	uint_32 flags=0;
     
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
//	   fprintf(serial_fd,".");
//   }
//   
//   fprintf(serial_fd,"\r\nHELLO!!!\r\n");
//   fprintf(serial_fd,"Starting system...\r\n");
//   printf("Hello\r\n");
   
   /* RTCS init */
    rtcs_init();
         
   for (;;)  
   {
      /* Run the shell */
	   printf("starting");
      Shell(Shell_commands, "ttyd:");//NULL);
      printf("Shell exited, restarting...\n");
   }

   
}
/* EOF */
