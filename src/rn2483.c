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
// Converts buff into a string representation of it hexadecimal representation
static void get_hex_string(uint8_t *buff, int buff_len, char *ret)
{
    int j;  //index of buff
    int i;  //index of string
    uint8_t nibble;
    const char hex_map[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    for (i = 0, j = 0; i < buff_len*2; i++)
    {
        nibble = 20;    // out of bounds of hex_map

        if (i % 2 == 0)
            nibble = (buff[j] >> 4) & 0x0F;
        else
        {
            nibble = buff[j] & 0x0F;
            j++;
        }

        ret[i] = hex_map[nibble];
    }

    return;
}
// Reads from the RX buffer into response until '\n' or EOB
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
            //@TODO add delay here? -testing
            response[0] = '\0';
            if (RN2483_response((uint8_t *)response) != RN2483_ERR_PANIC)
                ret = (strcmp(response, "accepted\r\n")? RN2483_SUCCESS : RN2483_DENIED);
            else
                ret = RN2483_ERR_PANIC;
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
int RN2483_tx(const void *buff, bool confirm, char *downlink)
{
    int ret = RN2483_ERR_PANIC;
    char *response = (char *)malloc(RN2483_MAX_BUFF);

    // figure out max payload length based on data rate
    int max_len = 0;
	if (strcmp(LoRaWAN_DataRate, "0") == 0 || strcmp(LoRaWAN_DataRate, "1") == 0 || strcmp(LoRaWAN_DataRate, "2") == 0)
		max_len = 59;
	else if (strcmp(LoRaWAN_DataRate, "3") == 0)
		max_len = 123;
	else if (strcmp(LoRaWAN_DataRate, "4") == 0 || strcmp(LoRaWAN_DataRate, "5") == 0 || strcmp(LoRaWAN_DataRate, "6") == 0 || strcmp(LoRaWAN_DataRate, "7") == 0)
		max_len = 230;
	else
		max_len = 230;

    // get payload
    char *payload = (char *)malloc(strlen(buff)*2); // 1 byte = 2 hex chars
    get_hex_string((uint8_t *)buff, strlen(buff), payload); // see documentation notes on this

    // send command
    char *cmd = malloc(max_len);
    if (confirm)
        sprintf(cmd, "mac tx cnf %s %s\r\n", LoRaWAN_Port, payload);
    else
        sprintf(cmd, "mac tx uncnf %s %s\r\n", LoRaWAN_Port, payload);
    ret = RN2483_command(cmd, response);

    if (ret == RN2483_SUCCESS)
    {
        // if initial response success, wait for tx success
        if (strcmp(response, "ok\r\n") == 0)
        {
            //@TODO add delay here? -testing
            response[0] = '\0';
            if (RN2483_response((uint8_t *)response) != RN2483_ERR_PANIC)
            {
                if (strcmp(response, "mac_tx_ok\r\n") == 0)
                    ret = RN2483_NODOWN;
                else if (strcmp(response, "mac_err\r\n") == 0 || strcmp(response, "invalid_data_len\r\n") == 0)
                    ret = RN2483_ERR_PANIC;
                else //assume downlink data
                {
                    memcpy(downlink, response, strlen(response));
                    return RN2483_SUCCESS;
                }
            }
        }
        // else return err code
        else if (strcmp(response, "invalid_param\r\n") == 0)
            ret = RN2483_ERR_PARAM;
        else if (strcmp(response, "no_free_ch\r\n") == 0)
            ret = RN2483_ERR_BUSY;
        else if (strcmp(response, "not_joined\r\n") == 0 || strcmp(response, "frame_counter_err_rejoin_needed\r\n") == 0)
            ret = RN2483_ERR_JOIN;
        else if (strcmp(response, "silent\r\n") == 0 || strcmp(response, "busy\r\n") == 0 || strcmp(response, "mac_paused\r\n") == 0)
            ret = RN2483_ERR_STATE;
        else if (strcmp(response, "invalid_data_len\r\n") == 0)
            ret = RN2483_ERR_PANIC;
    }

    free(cmd);
    free(response);
    return ret;
}

