//Authors: Gustavo Lodi, Nicholas Peçanha, Gustavo Malazavi
//Goal: Meteorological Station for Microclimates using knowledge adquired with Embedded Systems subject at Univeristy of São Paulo

//LIBs

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

void main(void)
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
	int digital_Temp2= (bin1[2] + bin[3] * 256);
	if(digital_Temp2 > 32767)
	{
	  digital_Temp2 -= 65536;
	}
	int digital_Temp3 = (bin1[4] + bin1[5] *256);
	if(digital_Temp3 > 32767)
	{
	  digital_Temp3 -= 65536;
	}

	// Get pressure coefficents and convert data
	int digital_Pres1 = (bin1[6] + bin1[7] * 256);
	int digital_Pres2 = (bin1[8] + bin1[9] * 256);
	if(digital_Pres2 > 32767)
	{
		digital_Pres2 -= 65536;
	}
	int digital_Pres3 = (bin1[10] + bin1[11] * 256);
	if(digital_Pres3 > 32767)
	{
		digital_Pres3 -= 65536;
	}
	int digital_Pres4 = (bin1[12] + bin1[13] * 256);
	if(digital_Pres4 > 32767)
	{
		digital_Pres4 -= 65536;
	}
	int digital_Pres5 = (bin1[14] + bin1[15] * 256);
	if(digital_Pres5 > 32767)
	{
	digital_Pres5 -= 65536;
	}
	int digital_Pres6 = (bin1[16] + bin1[17] * 256);
	if(digital_Pres6 > 32767)
	{
		digital_Pres6 -= 65536;
	}
	int digital_Pres7 = (bin1[18] + bin1[19] * 256);
	if(digital_Pres7 > 32767)
	{
		digital_Pres7 -= 65536;
	}
	int digital_Pres8 = (bin1[20] + bin1[21] * 256);
	if(digital_Pres8 > 32767)
	{
	digital_Pres8 -= 65536;
	}
	int digital_Pres9 = (bin1[22] + bin1[23] * 256);
	if(digital_Pres9 > 32767)
	{
		digital_Pres9 -= 65536;
	}
  	
	// Select register to control measurement(0xF4)
	// Normal mode, temp and pressure = 1(0x27)
	char preset[2] = {0};
	char info[8] = {0};
	preset[0] = 0xF4;
	preset[1] = 0x27;
	write(arch, preset, 2);
	// Select config register(0xF5)
	// Stand_by time = 1000 ms(0xA0)
	preset[0] = 0xF5;
	preset[1] = 0xA0;
	write(arch, preset, 2);

	// Read 8 bytes of data from register(0xF7)
	// pressure e temperature most and least significant bits
	rg1[0] = 0xF7;
	write(arch, rg1, 1);
	read(arch, info, 8);

	// Convert pressure and temperature info to 19-bits
	long p_conv = ((long)(info[0] * 65536 + ((long)(info[1] * 256) + (long)(info[2] & 0xF0)))) / 16;
	long t_conv = ((long)(info[3] * 65536 + ((long)(info[4] * 256) + (long)(info[5] & 0xF0)))) / 16;
	
	// Temperature offset calculations
	float temp_off1 = (((float)t_conv) / 16384.0 - ((float)digital_Temp1) / 1024.0) * ((float)digital_Temp2);
	float temp_off2 = ((((float)t_conv) / 131072.0 - ((float)digital_Temp1) / 8192.0) * (((float)adc_t)/131072.0 - ((float)digital_Temp1)/8192.0)) * ((float)digital_Temp3);
	
	//Calculations in absolute, celsius and fahrenheit 
	float t_abs = (long)(temp_off1 + temp_off2);
	float t_cel = (temp_off1 + temp_off2) / 5120.0;
	float t_fahr = t_cel * 1.8 + 32;

	// Pressure offset calculations
	pres_off1 = ((float)t_abs / 2.0) - 64000.0;
	pres_off2 = pres_off1 * pres_off1 * ((float)digital_Pres6) / 32768.0;
	pres_off2 = pres_off2 + pres_off1 * ((float)digital_Pres5) * 2.0;
	pres_off2 = (pres_off2 / 4.0) + (((float)digital_Pres4) * 65536.0);
	pres_off1 = (((float) digital_Pres3) * pres_off1 * pres_off1 / 524288.0 + ((float) digital_Pres2) * pres_off1) / 524288.0;
	pres_off1 = (1.0 + pres_off1 / 32768.0) * ((float)digital_Pres1);
	float pres_after = 1048576.0 - (float)p_conv;
	pres_after = (pres_after - (pres_off2 / 4096.0)) * 6250.0 / pres_off1;
	pres_off1 = ((float) digital_Pres9) * pres_after * pres_after / 2147483648.0;
	pres_off2 = pres_after * ((float) digital_Pres8) / 32768.0;
	float pressure_final = (pres_after + (pres_off1 + pres_off2 + ((float)digital_Pres7)) / 16.0) / 100;
	
	// Info to the user
	printf("Temperatura em Celsius : %.2f C \n\n", t_cel);
	printf("Temperatura em Fahrenheit : %.2f F \n\n", t_fahr);
	printf("Pressao : %.2f hPa \n\n", pressure_final);
	
}	
