#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main()
{
	int file;
	/*char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0)
	{
		printf("Sem conexão. \n");
		exit(1);
	}*/
	// Endereçamento
	ioctl(file, I2C_SLAVE, 0x76);

	// Ler bits do registrador
	char reg[1] = {0x88};
	write(file, reg, 1);
	char b1[24] = {0};
	if (read(file, b1, 24) != 24)
	{
		printf("Error : Input/Output error \n");
		exit(1);
	}

	// Conversão dos dados
	// temperatura
	int dig_T1 = (b1[0] + b1[1] * 256);
	int dig_T2 = (b1[2] + b1[3] * 256);
	if (dig_T2 > 32767)
	{
		dig_T2 -= 65536;
	}
	int dig_T3 = (b1[4] + b1[5] * 256);
	if (dig_T3 > 32767)
	{
		dig_T3 -= 65536;
	}

	// pressão
	int dig_P1 = (b1[6] + b1[7] * 256);
	int dig_P2 = (b1[8] + b1[9] * 256);
	if (dig_P2 > 32767)
	{
		dig_P2 -= 65536;
	}
	int dig_P3 = (b1[10] + b1[11] * 256);
	if (dig_P3 > 32767)
	{
		dig_P3 -= 65536;
	}
	int dig_P4 = (b1[12] + b1[13] * 256);
	if (dig_P4 > 32767)
	{
		dig_P4 -= 65536;
	}
	int dig_P5 = (b1[14] + b1[15] * 256);
	if (dig_P5 > 32767)
	{
		dig_P5 -= 65536;
	}
	int dig_P6 = (b1[16] + b1[17] * 256);
	if (dig_P6 > 32767)
	{
		dig_P6 -= 65536;
	}
	int dig_P7 = (b1[18] + b1[19] * 256);
	if (dig_P7 > 32767)
	{
		dig_P7 -= 65536;
	}
	int dig_P8 = (b1[20] + b1[21] * 256);
	if (dig_P8 > 32767)
	{
		dig_P8 -= 65536;
	}
	int dig_P9 = (b1[22] + b1[23] * 256);
	if (dig_P9 > 32767)
	{
		dig_P9 -= 65536;
	}

	char config[2] = {0};
	config[0] = 0xF2;
	config[1] = 0x01;
	write(file, config, 2);

	// Ler bits do registrador
	reg[0] = 0xA1;
	write(file, reg, 1);
	char data[8] = {0};
	read(file, data, 1);
	int dig_H1 = data[0];

	reg[0] = 0xE1;
	write(file, reg, 1);
	read(file, b1, 7);

	// Selecionar modo de leitura
	config[0] = 0xF4;
	config[1] = 0x27;
	write(file, config, 2);
	// Configurar registrador
	// Tempo de standby
	config[0] = 0xF5;
	config[1] = 0xA0;
	write(file, config, 2);

	// bits mais e menos significativos
	reg[0] = 0xF7;
	write(file, reg, 1);
	read(file, data, 8);

	// Conversão
	long adc_p = ((long)(data[0] * 65536 + ((long)(data[1] * 256) + (long)(data[2] & 0xF0)))) / 16;
	long adc_t = ((long)(data[3] * 65536 + ((long)(data[4] * 256) + (long)(data[5] & 0xF0)))) / 16;

	// Offset
	float var1 = (((float)adc_t) / 16384.0 - ((float)dig_T1) / 1024.0) * ((float)dig_T2);
	float var2 = ((((float)adc_t) / 131072.0 - ((float)dig_T1) / 8192.0) *
				  (((float)adc_t) / 131072.0 - ((float)dig_T1) / 8192.0)) *
				 ((float)dig_T3);
	float t_fine = (long)(var1 + var2);
	float cTemp = (var1 + var2) / 5120.0;
	float fTemp = cTemp * 1.8 + 32;

	// Offset da pressão
	var1 = ((float)t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((float)dig_P6) / 32768.0;
	var2 = var2 + var1 * ((float)dig_P5) * 2.0;
	var2 = (var2 / 4.0) + (((float)dig_P4) * 65536.0);
	var1 = (((float)dig_P3) * var1 * var1 / 524288.0 + ((float)dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0) * ((float)dig_P1);
	float p = 1048576.0 - (float)adc_p;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((float)dig_P9) * p * p / 2147483648.0;
	var2 = p * ((float)dig_P8) / 32768.0;
	float pressure = (p + (var1 + var2 + ((float)dig_P7)) / 16.0) / 100;

	// Output dos dados no terminal
	printf("Temperature in Celsius : %.2f C \n", cTemp);
	printf("Temperature in Fahrenheit : %.2f F \n", fTemp);
	printf("Pressure : %.2f hPa \n", pressure);
}
