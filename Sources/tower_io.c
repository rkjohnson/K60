#include <mqx.h>
#include <io_gpio.h>
#include <bsp.h>
#include "tower_io.h"




/*
 * Initialize GPIO for LED's and push buttons
 * This is also where you can set up more external GPIO
 */
boolean InitializeIO(void)
{
  const uint_32 output_set[] = {
    BSP_LED1 | GPIO_PIN_STATUS_0,
    BSP_LED2 | GPIO_PIN_STATUS_0,
    BSP_LED3 | GPIO_PIN_STATUS_0,
    BSP_LED4 | GPIO_PIN_STATUS_0,
    GPIO_LIST_END
  };

  const uint_32 input_set[] = {
    BSP_SW1,
    BSP_SW2,
    GPIO_LIST_END
  };

  /* Open and set port pins as output to drive LEDs (LED10 - LED13) */
  output_port = fopen("gpio:write", (char_ptr) &output_set);

  /* Open and set port pins as input to read value from switches */
  input_port = fopen("gpio:read", (char_ptr) &input_set);
	
  /* If successfully opened output port, write 0's to all pins */
  if (output_port)
    ioctl(output_port, GPIO_IOCTL_WRITE_LOG0, NULL);	


  return (input_port!=NULL) && (output_port!=NULL);
}

//Turn off all LEDs
void ResetOutputs(void)
{
   uint_32 i;

   for (i=0;i<MAX_OUTPUTS;i++) {
      SetOutput(i,FALSE);
   }
}

//Turn on and off LED outputs
void SetOutput(Output_t signal,boolean state)
{
   //Set up GPIO structure for each LED
   static const uint_32 led1[] = {
	BSP_LED1,
	GPIO_LIST_END
   };
   static const uint_32 led2[] = {
	BSP_LED2,
	GPIO_LIST_END
   };
   static const uint_32 led3[] = {
	BSP_LED3,
	GPIO_LIST_END
   };
   static const uint_32 led4[] = {
	BSP_LED4,
	GPIO_LIST_END
   };
	
	//If the output device driver was successfully opened...
	if (output_port)
	{
		//Set LED on or off based on the state passed to function
		switch (signal)
		{
             case LED1:
                ioctl(output_port, (state) ? GPIO_IOCTL_WRITE_LOG0 : GPIO_IOCTL_WRITE_LOG1, (pointer) &led1);
                break;
             case LED2:
                ioctl(output_port, (state) ? GPIO_IOCTL_WRITE_LOG0 : GPIO_IOCTL_WRITE_LOG1, (pointer) &led2);
                break;
             case LED3:
                ioctl(output_port, (state) ? GPIO_IOCTL_WRITE_LOG0 : GPIO_IOCTL_WRITE_LOG1, (pointer) &led3);
                break;
             case LED4:
                ioctl(output_port, (state) ? GPIO_IOCTL_WRITE_LOG0 : GPIO_IOCTL_WRITE_LOG1, (pointer) &led4);
                break;
         }
	}
}

//Get input from push buttons
boolean GetInput(Input_t signal)
{
   boolean  value=FALSE;

   //Set up GPIO structure
   static uint_32 data[] = {
		BSP_SW1,
                BSP_SW2,
		GPIO_LIST_END
	};

   //Read data from pins
   if (input_port) {
      ioctl(input_port, GPIO_IOCTL_READ,  &data);
   }

   //Parse data recieved
   switch (signal) {
      case SW1_INPUT:
         value = (data[0] & GPIO_PIN_STATUS)==0;
         break;
     case SW2_INPUT:
         value = (data[1] & GPIO_PIN_STATUS)==0;
         break;
   }

   return value;
}

