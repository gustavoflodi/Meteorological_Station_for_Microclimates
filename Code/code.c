//Authors: Gustavo Lodi, Nicholas Peçanha, Gustavo Malazavi
//Goal: Meteorological Station for Microclimates using knowledge adquired with Embedded Systems subject at Univeristy of São Paulo

//LIBs

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

void main()
{
  //The group decided to use I2C as the bus to connect peripherals
  int arch;
  char *barr = "/dev/i2c-1";
  
  //See if the bus is opened correctly
  if((arch = open(barr, O_RDWR)) < 0) 
	{
		printf("The Bus fail to open. \n");
		exit(1);
	}
  
  // Get I2C device, Address of the BME280 I2C bus is 0x76(136)
	ioctl(arch, I2C_SLAVE, 0x76);
