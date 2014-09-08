/*   This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/** \file
*	\brief		Command interpreter application specific functions
*	\author		Pat Satyshur
*	\version	1.1
*	\date		1/13/2013
*	\copyright	Copyright 2013, Pat Satyshur
*	\ingroup 	beer_heater_main
*
*	@{
*/

#include "main.h"
//#include "commands.h"
//#include <stdio.h>
//#include "board.h"

//The number of commands
const uint8_t NumCommands = 6;

//Handler function declarations

//Digital Output control function
static int _F1_Handler (void);
const char _F1_NAME[] 			= "setdo";
const char _F1_DESCRIPTION[] 	= "Turn valve on or off";
const char _F1_HELPTEXT[] 		= "setdo <DO channel> <state>";

//Set Servo Postion
static int _F2_Handler (void);
const char _F2_NAME[] 			= "setservo";
const char _F2_DESCRIPTION[] 	= "Set servo position";
const char _F2_HELPTEXT[] 		= "setservo <servo channel> <pos>";

//read Analog data
static int _F3_Handler (void);
const char _F3_NAME[]  			= "getai";
const char _F3_DESCRIPTION[]  	= "read analog inputs";
const char _F3_HELPTEXT[]  		= "'getai' has no parameters";

//read TC data
static int _F4_Handler (void);
const char _F4_NAME[]  			= "gettc";
const char _F4_DESCRIPTION[]  	= "read temperatures";
const char _F4_HELPTEXT[]  		= "'gettc' has no parameters";

//Set Command Sequence
static int _F5_Handler (void);
const char _F5_NAME[]  			= "setseq";
const char _F5_DESCRIPTION[]  	= "set command sequence";
const char _F5_HELPTEXT[]  		= "'setseq' <1> <2> <3>";//<DO channel> <time> <state>

//Read Time
static int _F6_Handler (void);
const char _F6_NAME[] 			= "gettime";
const char _F6_DESCRIPTION[] 	= "Get realtime clock time";
const char _F6_HELPTEXT[]		= "'gettime' has no parameters";

//start test sequence
static int _F7_Handler (void);
const char _F7_NAME[] 			= "fire";
const char _F7_DESCRIPTION[] 	= "start test sequence";
const char _F7_HELPTEXT[]		= "'fire' has no parameters";



//Send commands to DAC chip
static int _F8_Handler (void);
const char _F8_NAME[] 			= "setupdac";
const char _F8_DESCRIPTION[] 	= "Send DAC commands";
const char _F8_HELPTEXT[] 		= "dac <1> <2>";

//Send commands to ADC chip
static int _F9_Handler (void);
const char _F9_NAME[]  			= "setupadc";
const char _F9_DESCRIPTION[]  	= "Send ADC commands";
const char _F9_HELPTEXT[]  		= "setupadc <1> <2>";

//Send commands to TC chip
static int _F10_Handler (void);
const char _F10_NAME[]  			= "setuptc";
const char _F10_DESCRIPTION[]  	= "Send TC commands";
const char _F10_HELPTEXT[]  		= "setuptc <1> <2>";

//look for i2C devices
static int _F11_Handler (void);
const char _F11_NAME[]  			= "i2cscan";
const char _F11_DESCRIPTION[]  	= "Scan the I2C Bus";
const char _F11_HELPTEXT[]  		= "'i2cscan' has no parameters";




/*






//Set up the calibration for the internal temperature sensor
static int _F7_Handler (void);
const char _F7_NAME[] PROGMEM 			= "tempcal";
const char _F7_DESCRIPTION[] PROGMEM 	= "Calibrate the internal temperature sensor";
const char _F7_HELPTEXT[] PROGMEM 		= "'tempcal' has no parameters";

//Test the buzzer
static int _F8_Handler (void);
const char _F8_NAME[] PROGMEM 			= "beep";
const char _F8_DESCRIPTION[] PROGMEM 	= "Test the buzzer";
const char _F8_HELPTEXT[] PROGMEM 		= "beep <time>";

//Turn the relay on or off
static int _F9_Handler (void);
const char _F9_NAME[] PROGMEM 			= "relay";
const char _F9_DESCRIPTION[] PROGMEM 	= "Control the relay";
const char _F9_HELPTEXT[] PROGMEM 		= "relay <state>";

//Manual calibration of the ADC
static int _F10_Handler (void);
const char _F10_NAME[] PROGMEM 			= "cal";
const char _F10_DESCRIPTION[] PROGMEM 	= "Calibrate the ADC";
const char _F10_HELPTEXT[] PROGMEM 		= "'cal' has no parameters";

//Get temperatures from the ADC
static int _F11_Handler (void);
const char _F11_NAME[] PROGMEM 			= "temp";
const char _F11_DESCRIPTION[] PROGMEM 	= "Get temperatures from the ADC";
const char _F11_HELPTEXT[] PROGMEM 		= "'temp' has no parameters";

//Scan the TWI bus for devices
static int _F12_Handler (void);
const char _F12_NAME[] PROGMEM 			= "twiscan";
const char _F12_DESCRIPTION[] PROGMEM 	= "Scan for TWI devices";
const char _F12_HELPTEXT[] PROGMEM 		= "'twiscan' has no parameters";

//Dataflash functions
static int _F13_Handler (void);
const char _F13_NAME[] PROGMEM 			= "mem";
const char _F13_DESCRIPTION[] PROGMEM 	= "dataflash functions";
const char _F13_HELPTEXT[] PROGMEM 		= "mem <1> <2> <3>";
*/

//Command list
const CommandListItem AppCommandList[] =
{
	{ _F1_NAME,		1,  2,	_F1_Handler,	_F1_DESCRIPTION,	_F1_HELPTEXT	},		//Set Digital Output Channel
	{ _F2_NAME,		1,  2,	_F2_Handler,	_F2_DESCRIPTION,	_F2_HELPTEXT	},		//Set servo position
	{ _F3_NAME, 	1,  2,	_F3_Handler,	_F3_DESCRIPTION,	_F3_HELPTEXT	},		//read Analog data
	{ _F4_NAME, 	0,  0,	_F4_Handler,	_F4_DESCRIPTION,	_F4_HELPTEXT	},		//read TC data
	{ _F5_NAME, 	0,  3,	_F5_Handler,	_F5_DESCRIPTION,	_F5_HELPTEXT	},		//Set Command Sequence
	{ _F6_NAME, 	0,  0,	_F6_Handler,	_F6_DESCRIPTION,	_F6_HELPTEXT	},		//Read Time
	{ _F7_NAME, 	0,  0,	_F7_Handler,	_F7_DESCRIPTION,	_F7_HELPTEXT	},		//start test sequence

	{ _F8_NAME,		1,  1,	_F8_Handler,	_F8_DESCRIPTION,	_F8_HELPTEXT	},		//setupdac: Send commands to DAC chip
	{ _F9_NAME,		1,  1,	_F9_Handler,	_F9_DESCRIPTION,	_F9_HELPTEXT	},		//setupadc: Send commands to ADC chip
	{ _F10_NAME,	0,  0,	_F10_Handler,	_F10_DESCRIPTION,	_F10_HELPTEXT	},		//setuptc: Send commands to TC chip
	{ _F11_NAME,	0,  0,	_F11_Handler,	_F11_DESCRIPTION,	_F11_HELPTEXT	},		//i2cscan
	/*
	{ _F12_NAME,	0,  0,	_F12_Handler,	_F12_DESCRIPTION,	_F12_HELPTEXT	},		//twiscan
	{ _F13_NAME,	1,  3,	_F13_Handler,	_F13_DESCRIPTION,	_F13_HELPTEXT	},		//twiscan
	*/
};

//Command functions

//Digital Output control function
static int _F1_Handler (void)
{
	uint8_t n;

	//argAsInt(1) is Digital Output channel
	//argAsInt(2) is state of valve
	if(NumberOfArguments() == 2)
	{
		Board_DO_Set(argAsInt(1), argAsInt(2));
	}
	else
	{
		//Turn off all channels
		for (n=1;n<=TOTAL_DO_CHANNELS;n++)
		{
			Board_DO_Set(n, 0);
		}

	}
	return 0;
}

//Servo Valve Control Function
static int _F2_Handler (void)
{
	uint8_t n;

	//argAsInt(1) is Digital Output channel
	//argAsInt(2) is state of valve
	if(NumberOfArguments() == 2)
	{
		//Board_DO_Set(argAsInt(1), argAsInt(2));
	}
	else
	{
		//Turn off all valves


	}
	return 0;
}

//read Analog Inputs
static int _F3_Handler (void)
{

	uint8_t channel;
	uint8_t chipsel;
	uint16_t DataSet[8];

	//read analog channel data
	for(chipsel=0;chipsel<AI_CHIPS;chipsel++)
	{
		//get analog data from chip "chipsel"
		AD7606GetDataSet(chipsel, DataSet);

		for(channel=0;channel<AI_CHANNELS_PER_CHIP;channel++)
		{
		 printf("ADC[%u]: %d counts\r\n", channel, DataSet[channel]);
		 //analogBuffer[channel] = DataSet[channel-chipsel*AI_CHANNELS_PER_CHIP];
		}
	}



	if( xSemaphoreTake( dataSemaphore, ( portTickType ) 100 ) == pdTRUE )	//take data buffer semaphore
	{
		for(i=0; i<8; i++)
		{
			//printf("ADC[%u]: 0x%02X, 0x%02X,", i, ADC_DataArray2[i*2], ADC_DataArray2[i*2+1]);
			//ADC_DataArray[i] = (int16_t)((ADC_DataArray2[i*2] & 0xFF) << 8);
			//ADC_DataArray[i] |= (int16_t)((ADC_DataArray2[i*2+1]) & 0xFF);
			//printf(" %d counts\r\n", ADC_DataArray[i]);

			//dataTime
			//analogBuffer
			//TCbuffer
			//ServoPosition
			printf("ADC[%u]: %d counts\r\n", i, analogBuffer[i]);
		}

		//give data buffer semaphore
		xSemaphoreGive(dataSemaphore);
	}
	else
	{
		// We could not obtain the semaphore and can therefore not access
		// the shared resource safely.
	}



	return 0;
}

//read Temperatures
static int _F4_Handler (void)
{

	 uint8_t sel;
	 uint16_t coldJunction;
	 uint32_t temperature;

	for(sel=0;sel<4;sel++)
	{
		temperature=MAX31855read(sel, &coldJunction);
		printf("TC%u: %u\r\n",sel,temperature);
	}

	return 0;
}

//Set Command Sequence
static int _F5_Handler (void)
{

	return 0;
}


static int _F6_Handler (void)
{
	printf("Chip Status:\r\n");
	printf("Input Clock Rate: %u MHz\r\n", Chip_Clock_GetMainOscRate()/1000000);
	printf("System Clock Rate: %u MHz\r\n", Chip_Clock_GetSystemClockRate()/1000000);
	printf("Peripheral Clock Rate: %u MHz\r\n", Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_TIMER2)/1000000);
	printf("CompileDate: %s%s\r\n",__DATE__,__TIME__);

	return 0;
}


//Fire.  Start test sequence
static int _F7_Handler (void)
{

	// Emergency Stop
	xTaskCreate(vEStopTask, (signed char *) "vEStopTask",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				&vEStopTaskHandle);

	// Control Digital Outputs and Servos during run time
	xTaskCreate(vFireControlTask, (signed char *) "vFireControlTask",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2UL),
				&vFireControlTaskHandle);


	//setup E-Stop interrupt


	//suspend UART input/output tasks during run time.
	//vTaskSuspend(vRunCommandTask);
	//vTaskSuspend(vUARTTask);


	return 0;
}


//setupdac: Send commands to DAC chip
static int _F8_Handler (void)
{
	//send commands to the Analog Output chip

	//uint8_t command2 = argAsInt(2);
	//uint8_t SendBuffer[4];

	uint8_t CommandNumber = argAsInt(1);
	uint16_t DACVaule = argAsInt(2);

	if((CommandNumber > 0) && (CommandNumber < 6))
	{
		printf("Set DAC %u to 0x%04X\r\n", CommandNumber, DACVaule);
		AD5666SetVoltage(CommandNumber, DACVaule);
	}

	else
	{
		switch(CommandNumber)
		{
		case 6:
			//Modify the CS pin
			printf("Select %u\r\n", DACVaule);
			AD5666Select((uint8_t)DACVaule);
			break;

		case 7:
			//Modify the update pin
			printf("Update %u\r\n", DACVaule);
			AD5666Update((uint8_t)DACVaule);
			break;

		case 8:
			//Modify the clear pin
			printf("Clear %u\r\n", DACVaule);
			AD5666Clear((uint8_t)DACVaule);
			break;

		}
	}

	return 0;
}

//setupadc: Send commands to ADC chip
static int _F9_Handler (void)
{
	uint8_t channel;
	uint8_t chipsel;
	uint16_t DataSet[8];

	if(NumberOfArguments() >= 2)
	{
		switch (argAsInt(1))
		{
		case 1:
			printf("Setup 0x%02X\r\n", TCA9554A_GetConfig(0x38));
			break;

		case 2:
			TCA9554A_SetConfig(0x38, argAsInt(2));
			printf("OK\r\n");
			break;

		case 3:
			printf("State 0x%02X\r\n", TCA9554A_GetState(0x38));
			break;

		case 4:
			TCA9554A_SetState(0x38, argAsInt(2));
			printf("OK\r\n");
			break;

		case 5:
			TCA9554A_SetStateBit(0x38, argAsInt(2), argAsInt(3));
			printf("OK\r\n");
			break;

		case 6:
			TCA9554A_SetStateBits(0x38, argAsInt(2), argAsInt(3));
			printf("OK\r\n");
			break;

		case 7:
			printf("start timer at %u kHz\r\n", argAsInt(2));
			AD7606StartDataClock(argAsInt(2)*1000);
			//while(AD7606GetStatus() != AD7606_STATUS_DATAREADY) {}
			//AD7606GetDataSet();
			break;

		case 8:



			chipsel=0;

			//get analog data from chip "chipsel"
			AD7606GetDataSet(chipsel, DataSet);

			for(channel=0;channel<AI_CHANNELS_PER_CHIP;channel++)
			{
				printf("ADC[%u]: %d counts\r\n", channel, DataSet[channel]);
				//analogBuffer[channel] = DataSet[channel-chipsel*AI_CHANNELS_PER_CHIP];
			}


			/*
			uint8_t i;
			for(i=0; i<8; i++)
			{
				//printf("ADC[%u]: 0x%02X, 0x%02X,", i, ADC_DataArray2[i*2], ADC_DataArray2[i*2+1]);
				//ADC_DataArray[i] = (int16_t)((ADC_DataArray2[i*2] & 0xFF) << 8);
				//ADC_DataArray[i] |= (int16_t)((ADC_DataArray2[i*2+1]) & 0xFF);
				//printf(" %d counts\r\n", ADC_DataArray[i]);
				printf("ADC[%u]: %d counts\r\n", i, ADC_DataArray[i]);
			}
*/
			break;

		case 9:
			AD7606_Start(argAsInt(2));
			break;
		}
	}
	return 0;
}

//setuptc: Send commands to TC chip
static int _F10_Handler (void)
{


	return 0;
}

//i2cscan
static int _F11_Handler (void)
{
	uint8_t i;
	uint8_t DummyByte = 0x0A;

	printf("Scanning I2C Bus\r\n");

	for (i = 0; i <= 0x7F; i++)
	{
		if(Chip_I2C_MasterSend(I2C0, i, &DummyByte, 1) > 0)
		{
			printf("Device responded at 0x%02X\r\n", i);
		}
	}
	printf("Scan complete\r\n");
	return 0;
}







/** @} */
