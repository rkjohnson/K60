#ifndef __tower_io_h__
#define __tower_io_h__


typedef enum {
   LED1=0,
   LED2,
   LED3,
   LED4,
   MAX_OUTPUTS
} Output_t;

typedef enum {
   SW1_INPUT=0,
   SW2_INPUT,
   MAX_INPUTS
} Input_t;

static FILE_PTR input_port=NULL, output_port=NULL;

boolean InitializeIO(void);
boolean GetInput(Input_t);
void SetOutput(Output_t,boolean);
void ResetOutputs(void);

#endif