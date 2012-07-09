/**************************************************************************
*
* FileName: ADC_Task.c
*
* Comments:
* Task initializes ADC1 module, and then samples Channel 20 (temp sensor)
*  and Channel 26 (connected to on-board pot).
*
* This code does not use the MQX ADC driver since it has not been ported yet to
*  Kinetis. All the code in this file is bare-metal
*
*
***************************************************************************/

#include <string.h>
#include "demo.h"
#include "adc16.h"

tADC_Config Master_Adc_Config;
tADC_Cal_Blk CalibrationStore[2];

void InitializeADC();


  /*
   * This task configures the ADC module
   *
   * It then samples Channel 26 which has the ADC temperature sensor, and calculates
   *   the temperature
   *
   * Then it samples Channel 20 to read the value on the potentiometer
   *
   * Task then waits 500ms before sampling values again
   */
void adc_task()
{
  float temp;
  float vtemp;
  float pot;
  unsigned int value;

  printf("Starting ADC Task\n");

  InitializeADC();

  while(1)
  {
    //Read temperature value
    ADC1_SC1A = AIEN_OFF | ADC_SC1_ADCH(26);
    while ( (ADC1_SC1A & ADC_SC1_COCO_MASK) == COCO_NOT );  // Wait conversion end
    value=ADC1_RA;

    //Convert voltage to C
    vtemp=((float)value/65535)*3.3;
    temp=(vtemp-.7012)/.001646;
    temp=25-temp;
    Sensor.temp_int=(uint_8)temp;
    Sensor.temp_dec=(uint_8)((int)(temp*100))%10;
    //printf("Temp = %d.%d\n",Sensor.temp_int,Sensor.temp_dec);

    //Read Pot value
    ADC1_SC1A = AIEN_OFF | ADC_SC1_ADCH(20);
    while ( (ADC1_SC1A & ADC_SC1_COCO_MASK) == COCO_NOT );  // Wait conversion end
    value=ADC1_RA;

    //Convert to percentage
    pot=((float)value/65535)*100;
    Sensor.pot=(uint_8)pot;
    // printf("Pot %d%\n",Sensor.pot);

    //Time Delay task to allow other tasks to run
    _time_delay(500);
  }
}

void InitializeADC()
{
  uint8_t cal_ok;
   /* Turn on the ADCo and ADC1 clocks */
  SIM_SCGC6 |= (SIM_SCGC6_ADC0_MASK );
  SIM_SCGC3 |= (SIM_SCGC3_ADC1_MASK );

  /* setup the initial configuration */
  Master_Adc_Config.CONFIG1  = ADLPC_NORMAL | ADC_CFG1_ADIV(ADIV_4) | ADLSMP_LONG | ADC_CFG1_MODE(MODE_16)| ADC_CFG1_ADICLK(ADICLK_BUS);
  Master_Adc_Config.CONFIG2  = MUXSEL_ADCA | ADACKEN_DISABLED | ADHSC_HISPEED | ADC_CFG2_ADLSTS(ADLSTS_20) ;
  Master_Adc_Config.COMPARE1 = 0x1234u ;
  Master_Adc_Config.COMPARE2 = 0x5678u ;
  Master_Adc_Config.STATUS2  = ADTRG_SW | ACFE_DISABLED | ACFGT_GREATER | ACREN_ENABLED | DMAEN_DISABLED | ADC_SC2_REFSEL(REFSEL_EXT);
  Master_Adc_Config.STATUS3  = CAL_OFF | ADCO_SINGLE | AVGE_DISABLED | ADC_SC3_AVGS(AVGS_32);
  Master_Adc_Config.PGA      = PGAEN_DISABLED | PGACHP_NOCHOP | PGALP_NORMAL | ADC_PGA_PGAG(PGAG_64);
  Master_Adc_Config.STATUS1A = AIEN_OFF | DIFF_SINGLE | ADC_SC1_ADCH(31);
  Master_Adc_Config.STATUS1B = AIEN_OFF | DIFF_SINGLE | ADC_SC1_ADCH(31);

  ADC_Config_Alt(ADC1_BASE_PTR, &Master_Adc_Config);  // config ADC
  cal_ok = ADC_Cal(ADC1_BASE_PTR);                    // do the calibration
  ADC_Read_Cal(ADC1_BASE_PTR,&CalibrationStore[1]);   // store the cal
}

