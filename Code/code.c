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
  
  //Read 24 bytes of data from register (0x88)
  char rg1[1] = {0x88};
  write(arch, rg1, 1);
  char bin1[24] = {0};
  if(read(arch,bin1,24) != 24)
  {	
	  printf("Error: Input/Output error \n");
	  exit(1);
  }

  // Convert data, temp coefficents
  int digital_Temp1 = (bin1[0] + bin1[1]*256);
  int dgitial_Temp2= (bin1[2] + bin[3] * 256);
  if(digital_Temp2 > 32767)
  {
	  digital_Temp2 -= 65536;
  }
  int digital_Temp3 = (bin1[4] + bin1[5] *256);
  if(digital_Temp3 > 32767)
  {
	  digital_Temp3 -= 65536;
  }
	

  
	
	
