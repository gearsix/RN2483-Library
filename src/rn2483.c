/*!
	@file	rn2483.c
	@author	Alexander Collins (alexander-collins@outlook.cm)
	@date	September 2017 - April 2018
	@brief	A library for embedded platforms that allows for interaction with a Microchip RN2483.

	@see rn2483.h
*/
//========
// MACROS
//========
//includes
#include "rn2483.h"

//===========
// FUNCTIONS
//===========
//PRIVATE
// Reads from the RX buffer into response until '\n' or EOB
/*!
	TODO
*/
static int RN2483_response(uint8_t *response)
{
	int i = 0;

	while (*response != '\n' && i < RN2483_MAX_BUFF)
	{
		*response++ = fgetc(stdin);
		i++;
	}

    if (response <= 0)
        return RN2483_PANIC
    else
    	return i;
}

//PUBLIC
//system
// Sends a command to the RN2483 and sets the resposne in buffer
int RN2483_command(const char *command, char *response)
{
	//check command ends with \r\n (easy to forget)
	int end = strlen(command);
	if (command[end-1] != '\r' || command[end] != '\n')
		return RN2483_ERR_PARAM;
	
	//send command
	fprintf(stdout, command);

	//recv response
	return RN2483_response((uint8_t *)response);
}
// Retrieves the firmware version of the RN2483 module and stores it in buff.
int RN2483_firmware(char *buff)
{
	return RN2483_command("sys get ver\r\n", buff);
}

//LoRa
// Initialises all the RN2483 MAC settings required to run LoRa commands (join, tx, etc).
int RN2483_initMAC()
{
	int ret = RN2483_ERR_PANIC;
	char *response = (char *)malloc(RN2483_MAX_BUFF);

	do {
		ret++;
		switch(ret)
		{
			case 0:	//reset MAC
				ret = RN2483_command("mac reset " LoRaWAN_Freqency, response);
				break;
			case 1:	// set DevAddr
				ret = RN2483_command("mac set devaddr " LoRaWAN_DevAddr, response);
				break;
			case 2:	//set DevEui
				ret = RN2483_command("mac set deveui " LoRaWAN_DevEUI, response);
				break;
			case 3:	//set AppEui
				ret = RN2483_command("mac set appeui " LoRaWAN_AppEUI, response);
				break;
			case 4:	//set AppKey
				ret = RN2483_command("mac set appkey " LoRaWAN_AppKey, response);
				break;
			case 5:	//set DataRate
				ret = RN2483_command("mac set dr " LoRaWAN_DataRate, response);
				break;
		}
	} while (ret == RN2483_SUCCESS && strcmp(response, "ok") == 0);

	return ret;
}
