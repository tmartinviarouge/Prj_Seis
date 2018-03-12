#ifndef RPI2_H
#define RPI2_H


using namespace std;

class RPI2plus
{
public:
    enum BROCHES_GPIO_ETENDU
    {
//	nom broche BCM	= num broche physique	   //correspondance WiringPi
//	***************    ******************	    ***********************
	I2C_SDA		= 3, 	//------------------>	WiringPi_8
	I2C_SDL		= 5,	//------------------>	WiringPi_9

	SPI_CE0		= 24,	//------------------>	WiringPi_10
	SPI_CE1		= 26, 	//------------------>	WiringPi_11
	SPI_MOSI	= 19, 	//------------------>	WiringPi__12
	SPI_MISO	= 21, 	//------------------>	WiringPi_13
	SPI_SCLK	= 23, 	//------------------>	WiringPi_14

        GPIO_04		= 7, 	//------------------>	WiringPi_7
        GPIO_05		= 29, 	//------------------>	WiringPi_21
        GPIO_06		= 31, 	//------------------>	WiringPi_22
        GPIO_12		= 32, 	//------------------>	WiringPi_26
        GPIO_13		= 33, 	//------------------>	WiringPi_23
        GPIO_16		= 36, 	//------------------>	WiringPi_27
        GPIO_17		= 11,	//------------------>	WiringPi_0
        GPIO_18		= 12, 	//------------------>	WiringPi_1
        GPIO_19		= 35, 	//------------------>	WiringPi_24
        GPIO_20		= 38, 	//------------------>	WiringPi_28
        GPIO_21		= 40, 	//------------------>	WiringPi_29
        GPIO_22		= 15,	//------------------>	WiringPi_3
        GPIO_23		= 16, 	//------------------>	WiringPi_4
        GPIO_24		= 18, 	//------------------>	WiringPi_5
        GPIO_25		= 22, 	//------------------>	WiringPi_6
        GPIO_26		= 37,	//------------------>	WiringPi_25
        GPIO_27		= 13, 	//------------------>	WiringPi_2

	UART_TXD	= 8, 	//------------------>	WiringPi_15
	UART_RXD	= 10 	//------------------>	WiringPi_16
    };
	
	enum GPIO_WIRINGPI
	{
		WP_GPIO_0	=	0,	//broche 11
		WP_GPIO_1	=	1,	//broche 12
		WP_GPIO_2	=	2,	//broche 13
		WP_GPIO_3	=	3,	//broche 15
		WP_GPIO_4	=	4,	//broche 16
		WP_GPIO_5	=	5,	//broche 18
		WP_GPIO_6	=	6,	//broche 22
		WP_GPIO_7	=	7,	//broche 7
		WP_GPIO_21	=	21,	//broche 29
		WP_GPIO_22	=	22,	//broche 31
		WP_GPIO_23	=	23,	//broche 33
		WP_GPIO_24	=	24,	//broche 35
		WP_GPIO_25	=	25,	//broche 37
		WP_GPIO_26	=	26,	//broche 32
		WP_GPIO_27	=	27,	//broche 36
		WP_GPIO_28	=	28,	//broche 38
		WP_GPIO_29	=	29,	//broche 40
		
	};

 };


#endif	//RPI2_H
