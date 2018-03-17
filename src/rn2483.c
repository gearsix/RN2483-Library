/*!
	@file	rn2483.c
	@author	Alexander Collins (alexander-collins@outlook.cm)
	@date	September 2017 - April 2018
	@brief	A library for embedded platforms that handles interaction with a Microchip RN2483.

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

	return i;
}

//PUBLIC
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

