# K60 Tower Project
---

* Networking w/ telnet
* Shell

## Build steps

1. replace $MQX$/config/twrk60n512/user_config.h with the one from this project (probably best to save the original)
2. modify $MQX$/mqx/source/bsp/twrk60n512/twrk60n512.h as follows:

	// enable interrupts for TTYD
	#define BSPCFG_ENABLE_ITTYD    1
	
Change to use ITTYD for standard print functions (printfs)
	/*
	 * Other Serial console options:(do not forget to enable BSPCFG_ENABLE_TTY define if changed)
	 *      "ittyf:"     OSJTAG-COM  interrupt mode
	 *      "ttyd:"      TWR-SER     polled mode
	 *      "ittyd:"     TWR-SER     interrupt mode
	 *      "iodebug:"   IDE debug console
	 */
	#ifndef BSP_DEFAULT_IO_CHANNEL
	    #if BSPCFG_ENABLE_TTYF
	        //#define BSP_DEFAULT_IO_CHANNEL                    "ttyf:"    /* OSJTAG-COM   polled mode   */
	        #define BSP_DEFAULT_IO_CHANNEL                    "ittyd:"    /* TWR-SER     interrupt mode   */
	        #define BSP_DEFAULT_IO_CHANNEL_DEFINED
	    #else
	        #define BSP_DEFAULT_IO_CHANNEL                      NULL
	    #endif
	#endif