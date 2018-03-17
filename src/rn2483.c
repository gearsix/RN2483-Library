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

    if (i <= 0)
        return RN2483_ERR_PANIC;
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
	if (RN2483_response((uint8_t *)response) != RN2483_ERR_PANIC)
        return RN2483_SUCCESS;
	else
        return RN2483_ERR_PANIC;
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
				ret = RN2483_command("mac reset " LoRaWAN_Frequency "\r\n", response);
				break;
			case 1:	// set DevAddr
				ret = RN2483_command("mac set devaddr " LoRaWAN_DevAddr "\r\n", response);
				break;
			case 2:	//set DevEui
				ret = RN2483_command("mac set deveui " LoRaWAN_DevEUI "\r\n", response);
				break;
			case 3:	//set AppEui
				ret = RN2483_command("mac set appeui " LoRaWAN_AppEUI "\r\n", response);
				break;
			case 4:	//set AppKey
				ret = RN2483_command("mac set appkey " LoRaWAN_AppKey "\r\n", response);
				break;
			case 5:	//set DataRate
				ret = RN2483_command("mac set dr " LoRaWAN_DataRate "\r\n", response);
				break;
		}
	} while (ret == RN2483_SUCCESS && strcmp(response, "ok\r\n") == 0);

    free(response);
	return ret;
}
// Attempts to join a LoRa network using the specified mode.
int RN2483_join(int mode)
{
	int ret = RN2483_ERR_PANIC;
	char *response = (char *)malloc(RN2483_MAX_BUFF);

    // send command & recv initial response
	if (mode == RN2483_OTAA)
		ret = RN2483_command("mac join otaa\r\n", response);
	else if (mode == RN2483_ABP)
		ret = RN2483_command("mac join abp\r\n", response);
	else
		ret = RN2483_ERR_PARAM;

    if (ret == RN2483_SUCCESS)
    {
        // if initial response success, wait for network response
        if (strcmp(response, "ok\r\n") == 0)
        {
            //delay here -reqs testing?
            response[0] = '\0';
            if (RN2483_response((uint8_t *)response) != RN2483_ERR_PANIC)
                ret = (strcmp(response, "accepted\r\n")? RN2483_SUCCESS : RN2483_DENIED);
        }
        // else return err code
        else if (strcmp(response, "keys_not_init\r\n") == 0)
            ret = RN2483_ERR_KIDS;
        else if (strcmp(response, "no_free_ch\r\n") == 0)
            ret = RN2483_ERR_BUSY;
        else if (strcmp(response, "silent\r\n") == 0 || strcmp(response, "busy\r\n") == 0 || strcmp(response, "mac_paused\r\n") == 0)
            ret = RN2483_ERR_STATE;
	}

    free(response);
    return ret;
}
// Sends a confirmed/unconfirmed frame with an application payload of buff.
int RN2483_tx(const uint8_t *buff, bool confirm)
{
    int ret = RN2483_ERR_PANIC;
    char *response = (char *)malloc(RN2483_MAX_BUFF);


    free(response);
    return ret;
}

