# K60 Tower Project
---

* Networking w/ telnet
* Shell

## Prerequisites

1. Install CodeWarrior 10.2 (Special Edition): [Link](http://cache.freescale.com/lgfiles/devsuites/MCU/CW_MCU_v10.2_SE.exe?fpsp=1)
2. Install MQX 3.8: [Link](https://www.freescale.com/webapp/Download?colCode=FSLMQXOS_3_8_0&prodCode=MQX&appType=license&location=null&fpsp=1&Parent_nodeId=1228773250613737641153&Parent_pageType=product)
3. Install the MQX 3.8 patch for CW 10.2 (for kernel debugging): [Link](http://cache.freescale.com/files/microcontrollers/software/app_software/application_development_framework/MQX_3.8_INST_CW_MCU_10.2_UP_v1.0.0_SP.zip?fpsp=1)

## Build steps

1. replace $MQX$/config/twrk60n512/user_config.h with the one from this project (probably best to save the original)
2. modify $MQX$/mqx/source/bsp/twrk60n512/twrk60n512.h as follows:

    Enable interrupts for TTYD:

        #define BSPCFG_ENABLE_ITTYD    1
        
    Change to use ITTYD for standard print functions (`printf`'s)

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
                #define BSP_DEFAULT_IO_CHANNEL                      "ittyd:"    /* TWR-SER     interrupt mode   */
                #define BSP_DEFAULT_IO_CHANNEL_DEFINED
            #else
                #define BSP_DEFAULT_IO_CHANNEL                      NULL
            #endif
        #endif
3. Follow library building process described in $MQX$/doc/FSL_MQX_getting_started.pdf (p.7)
    > The libraries have to be built in correct order:

    > PSP and BSP 

    > MFS  

    > RTCS 

    > Shell and USB libraries 
4. Build K60 application
5. Load via debugger & run