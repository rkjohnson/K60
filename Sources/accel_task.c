//-----------------------------------------------------------------------------
/*
Copyright (c) 2012 JAR
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 * @file ACCEL_TASK.C
 *
 * Uses I2C driver to initialize and read MMA7660 Accelerometer
 *
 * @version $Id$
 */
//-----------------------------------------------------------------------------

/* #####   HEADER FILE INCLUDES   ################################################### */
#include "demo.h"
#include <i2c.h>

/* #####   VARIABLES  -  EXPORTED VARIABLES   ####################################### */
extern SENSOR_DATA Sensor;
extern unsigned char led_status;

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ################################### */
/* I2C Addresses for Sensors */
#define I2C_ACCELEROMETER_ADDRESS   0x4C      //MMA7660
#define I2C_DATA_SIZE               5

/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ######################### */

/* #####   DATA TYPES  -  LOCAL TO THIS SOURCE FILE   ############################### */

/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ################################ */
FILE_PTR fd;
uchar recv_buffer[I2C_DATA_SIZE];

/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ############################### */
void write_I2C(int i2c_device, uchar reg, uchar value);
void read_I2C(int i2c_device, int sensor, int length);
void print_accelerometer_data();
signed char convert_accel_data(signed char input);

/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ############################ */

// ===  FUNCTION  ======================================================================
//         Name:  accel_task
/**
 * @brief Task for reading the MMA7660 accelerometer data from the TWR-K60N512
 *        board, and displaying the data and other Kinetis data on a web server
 *
 * @param uint_32
 * 
 * @return void
 */
// =====================================================================================
void accel_task ( uint_32 data )
{
   uint_32 result;

   printf("Starting Accelerometer Task\n");

   /* initialize I2C driver */
   InitializeI2C();

   /* configure the MMA7660 */
   InitializeMMA7660();

   /*
    * Read the accelerometer data and store it in a global structure
    */
   while( TRUE )
   {
      /* read first five registers on MMA7660 */
      read_I2C( I2C_ACCELEROMETER_ADDRESS, 0x00, 5 );
      
      Sensor.mma7660_x = convert_accel_data( (int_8)recv_buffer[0] );
      Sensor.mma7660_y = convert_accel_data( (int_8)recv_buffer[1] );
      Sensor.mma7660_z = convert_accel_data( (int_8)recv_buffer[2] );
      Sensor.mma7660_status = recv_buffer[3];

      _time_delay( 300 );
      print_accelerometer_data();
   }

   /* Close the driver */
   result = fclose( fd );
   if( result ) {
      printf ("ERROR during close, returned: %d\n", result);
   }
}      /* -----  end of function accel_task  ----- */

/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ##################### */

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
   /* Configure the MMA7660 */
   write_I2C( I2C_ACCELEROMETER_ADDRESS, 0x09, 0xE0 );
   write_I2C( I2C_ACCELEROMETER_ADDRESS, 0x07, 0x19 );
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
   int n = length;

   /* the starting register for the particular sensor requested */
   uchar reg=sensor;

   /* set the I2C destination address */
   ioctl( fd, IO_IOCTL_I2C_SET_DESTINATION_ADDRESS, &i2c_device_address );

   /* tell the QE96 which sensor data to get */
   fwrite( &reg, 1, 1, fd); //data to write, size of unit, # of bytes to write, I2C device handl er

   /* wait for completion */
   fflush( fd );

   /* do a repeated start to avoid giving up control */
   ioctl( fd, IO_IOCTL_I2C_REPEATED_START, NULL );

   /* set how many bytes to read */
   ioctl( fd, IO_IOCTL_I2C_SET_RX_REQUEST, &n );

   /*
    * read n bytes of data and put it into the recv_buffer
    * buffer to read data into, size of unit, # of bytes to read, I2C device handler
    */
   fread( &recv_buffer, 1, n, fd );

   /* wait for completion */
   fflush( fd );

   /* send out stop */
   ioctl( fd, IO_IOCTL_I2C_STOP, NULL );
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

// ===  FUNCTION  ======================================================================
//         Name:  convert_accel_data
/**
 * @brief Convert 6-bit result into an 8-bit signed char
 *
 * @param signed char
 * 
 * @return signed char
 */
// =====================================================================================
signed char convert_accel_data ( signed char byte )
{
   byte &= ~0x40;       // Turn off alert bit
   if( byte & 0x20 ) {  // update 6-bit signed format to 8-bit signed format
      byte |= 0xE0;
   }
   return( byte );
}      /* -----  end of function convert_accel_data  ----- */
