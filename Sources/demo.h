#ifndef _demo_h_
#define _demo_h_
/**HEADER********************************************************************
*
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
* All Rights Reserved
*
***************************************************************************
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
**************************************************************************
*
* $FileName: HVAC.h$
* $Version : 3.5.21.0$
* $Date    : Dec-2-2009$
*
* Comments:
*   The main configuration file for WEB_HVAC demo
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <lwevent.h>
#include "tower_io.h"

//Task number for Sensor_task
#define INIT_TASK 1
#define IR_TASK 2
#define ADC_TASK 3
#define ACCEL_TASK 4
#define SHELL_TASK 5
#define SDCARD_TASK 6

/* Sensor Struct */
typedef struct
{
  int_8 mma7660_x;
  int_8 mma7660_y;
  int_8 mma7660_z;
  unsigned char mma7660_status;
  int_8 pot;
  int_8 temp_int;
  int_8 temp_dec;
} SENSOR_DATA;

typedef enum {
   BUTTON_0=0,
   BUTTON_1,
   BUTTON_2,
   BUTTON_3,
   BUTTON_4,
   BUTTON_5,
   BUTTON_6,
   BUTTON_7,
   BUTTON_8,
   BUTTON_9,
   POWER,
   CHANNEL_UP,
   CHANNEL_DOWN,
   VOLUME_UP,
   VOLUME_DOWN,
   UP,
   DOWN,
   RIGHT,
   LEFT,
   ENTER,
   NONE,
   MAX_BUTTONS
} REMOTE_BUTTONS;

extern REMOTE_BUTTONS remote;
extern SENSOR_DATA Sensor;
extern unsigned char led_status;
extern char ir_string[50];

/* Prototype for Tasks */
void Init_Task(uint_32);
void Accel_Task(uint_32);
void IR_Task();
void ADC_Task();
void shell_task(uint_32);
void sdcard_task(uint_32);

/* Helper Functions */
void read_mma7660();
void InitializeIR();
void InitializeI2C();
void InitializeMMA7660();
void clear_hscmp_registers();
void clear_lpt_registers();
void cmp0_isr(pointer);
void print_button(unsigned int button);





typedef struct my_isr_struct
{
   pointer               OLD_ISR_DATA;
   void      (_CODE_PTR_ OLD_ISR)(pointer);
   _mqx_uint             TICK_COUNT;
} MY_ISR_STRUCT, _PTR_ MY_ISR_STRUCT_PTR;

#endif
