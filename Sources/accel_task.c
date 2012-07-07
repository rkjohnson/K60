/**************************************************************************
*
* FileName: Accel_Task.c
*
* Comments: Uses I2C driver to initialize and read MMA7660 Accelerometer on the
*            the tower board
*
*
***************************************************************************/


#include "demo.h"
#include <i2c.h>


/* I2C Addresses for Sensors */
#define I2C_ACCELEROMETER_ADDRESS 0x4C      //MMA7660
#define I2C_DATA_SIZE 5

void write_I2C(int i2c_device, uchar reg, uchar value);
void read_I2C(int i2c_device, int sensor, int length);
void print_accelerometer_data();
signed char convert_accel_data(signed char input);

/* Global Variables */
extern SENSOR_DATA Sensor;
extern unsigned char led_status;

FILE_PTR fd;
uchar recv_buffer[I2C_DATA_SIZE];


/*
 * Task for reading the MMA7660 accelerometer data from the TWR-K60N512
 *  board, and displaying the data and other Kinetis data on a web server
 *
 */
void Accel_Task(uint_32 data)
{
  uint_32 result;

  printf("Starting Accelerometer Task\n");

  //Initialize I2C driver
  InitializeI2C();

  //Configure MMA7660
  InitializeMMA7660();


  /*
   * Read the accelerometer data and store it in a global structure
   */
  while (TRUE)
  {
    //Read first five registers on MMA7660
    read_I2C(I2C_ACCELEROMETER_ADDRESS,0x00,5);
  	
    Sensor.mma7660_x=convert_accel_data((int_8)recv_buffer[0]);
    Sensor.mma7660_y=convert_accel_data((int_8)recv_buffer[1]);
    Sensor.mma7660_z=convert_accel_data((int_8)recv_buffer[2]);
    Sensor.mma7660_status=recv_buffer[3];  	


     _time_delay(300);
    print_accelerometer_data();
   }

   /* Close the driver */
   result = fclose (fd);
   if (result)
   {
      printf ("ERROR during close, returned: %d\n", result);
   }
}

void InitializeI2C()
{
  /* Open the I2C driver, and assign a I2C device handler*/
  fd = fopen ("i2c0:", NULL);
  if (fd == NULL)
  {
    printf ("Failed to open the I2C driver!\n");
    _time_delay (200L);
    _mqx_exit (1L);
  }

  /* Set I2C into Master mode */
  ioctl (fd, IO_IOCTL_I2C_SET_MASTER_MODE, NULL);
}

void InitializeMMA7660()
{
  /* Configure MMA7660 */
  write_I2C(I2C_ACCELEROMETER_ADDRESS,0x09,0xE0);
  write_I2C(I2C_ACCELEROMETER_ADDRESS,0x07,0x19);
}

/* Function for writing data to I2C Sensor */
void write_I2C(int i2c_device_address, uchar reg, uchar value)
{
  uchar data[2];

  data[0]=reg;   //Sensor register
  data[1]=value; //Byte of data to write to register

  /* Set the destination address */
  ioctl (fd, IO_IOCTL_I2C_SET_DESTINATION_ADDRESS, &i2c_device_address);

  /* Write 2 bytes of data: the desired register and then the data */
  fwrite (&data, 1, 2, fd);  //data to write, size of unit, # of bytes to write, I2C device handler
  fflush (fd);

  /* Send out stop */
  ioctl (fd, IO_IOCTL_I2C_STOP, NULL);
}

/* Function for reading data from I2C. Data placed in recv_buffer */
void read_I2C(int i2c_device_address, int sensor, int length)
{
  int n=length;

  //The starting register for the particular sensor requested
  uchar reg=sensor;

  //Set the I2C destination address
  ioctl (fd, IO_IOCTL_I2C_SET_DESTINATION_ADDRESS, &i2c_device_address);

  //Tell the QE96 which sensor data to get
  fwrite (&reg, 1, 1, fd); //data to write, size of unit, # of bytes to write, I2C device handler

  //Wait for completion
  fflush (fd);

  //Do a repeated start to avoid giving up control
  ioctl (fd, IO_IOCTL_I2C_REPEATED_START, NULL);

  //Set how many bytes to read
  ioctl (fd, IO_IOCTL_I2C_SET_RX_REQUEST, &n);

  //Read n bytes of data and put it into the recv_buffer
  fread (&recv_buffer, 1, n, fd); //buffer to read data into, size of unit, # of bytes to read, I2C device handler

  //Wait for completion
  fflush (fd);

  //Send out stop
  ioctl (fd, IO_IOCTL_I2C_STOP, NULL);
}

void print_accelerometer_data()
{
  //MMA7660 Sensor
  printf("Accelerometer:\n");
  printf("  MMA7660 X-Axis: %d\n",Sensor.mma7660_x);
  printf("  MMA7660 Y-Axis: %d\n",Sensor.mma7660_y);
  printf("  MMA7660 Z-Axis: %d\n",Sensor.mma7660_z);
  printf("  MMA7660 Status: %02X\n",Sensor.mma7660_status);
}

/*!
 * Convert 6-bit result into an 8-bit signed char
 */
signed char convert_accel_data(signed char input)
{
      input &=~0x40; //Turn off alert bit
      if(input & 0x20)    // update 6-bit signed format to 8-bit signed format
	input |= 0xE0;
    return (signed char) input;
}