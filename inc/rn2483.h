/*!
	@file	rn2483.h
	@author	Alexander Collins (alexander-collins@outlook.com)
	@date	September 2017 - April 2018
	@brief	A library for embedded platforms that allows for interaction with a Microchip RN2483.

	@see https://www.microchip.com/wwwproducts/en/RN2483
	@see https://www.rs-online.com/designspark/rel-assets/ds-assets/uploads/knowledge-items/application-notes-for-the-internet-of-things/LoRaWAN%20Specification%201R0.pdf
*/

#ifndef RN2483
#define RN2483

//========
// MACROS
//========
//includes
// custom
#include "config.h"
// standard
#include <stdio.h>      //fgetc, fprintf
#include <string.h>     //strlen, strcmp
#include <stdint.h>     //uint8_t
#include <stdbool.h>    //bool
#include <stdlib.h>     //malloc
//defines
#define RN2483_MAX_BUFF	33 /**< Maximum(+1) number of characters returned by RN2483 responses */

//=========
// GLOBALS
//=========
//! Values returned by RN2483_* functions
enum RN2483_ReturnCodes {
	RN2483_SUCCESS,                 /**< Success */
	RN2483_ERR_PARAM,               /**< Error: invalid parameter passed to function */
	RN2483_EOB = RN2483_MAX_BUFF,	/**< Reached end of buffer passed to function */
    RN2483_ERR_KIDS,                /**< Error: tried to join a LoraWAN network without the correct keys & ids (kids) configured */
    RN2483_ERR_BUSY,                /**< Error: tried to join/tx but all configured frequency channels were busy, wait and try again */
    RN2483_ERR_STATE,               /**< Error: current state cannot perform action, see RN2483 documentation */
    RN2483_DENIED,                  /**< Join command went through, but the network denied your join request */
    RN2483_ERR_JOIN,                /**< Error: tried to tx data without being joined to a LoRaWAN network */
    RN2483_NODOWN,                  /**< tx succeeded and no downlink was received */
	RN2483_ERR_PANIC	            /**< Error: SOMETHING(???) went wrong. You found a bug! */
};
//! Valid LoRaWAN join modes @see RN2483_join(int mode)
enum RN2483_JoinModes {
    RN2483_OTAA,	/**< Over-the-Air-Activation */
	RN2483_ABP		/**< Activation-By-Personalization */
};

//===========
// FUNCTIONS
//===========
//system
//! Resets the RN2483 by toggling the RESET pin
/*!
	TODO
*/
int RN2483_reset();
//! Attempts to trigger the auto-baud detection sequence.
/*!
	TODO
*/
int RN2483_autobaud();
//! Write a command to the RN2483 and recieve it's response
/*!
    Send a command to the RN2483, if the command is valid the RN2483's response will be written 
    to response

    @return RN2483_ERR_PARAM if the command does not end in "\r\n" (required, see documentation)
    @return RN2483_SUCCESS command was successful and response was valid

    @see RN2483 LoRa Technology Module Command Reference User's Guide
*/
int	RN2483_command(const char *command, char *response);
//! Retrieves the firmware version of the RN2483 module and stores it in buff.
/*!
    If successful, buff should contain a string that looks like this:

        "RN2483 X.Y.Z MMM DD YYYY HH:MM:SS"

    where X.Y.Z is firmware version, MMM is month, DD is day, HH:MM:SS is hour, minutes, seconds.

        "sys get ver\r\n"

    @return RN2483_SUCCESS Successfully wrote the firmware version of RN2483 into response
    @return RN2483_ERR_PANIC Managed to read <= 0 bytes...
*/
int RN2483_firmware(char *buff);

//LoRa
//! Initialises all the RN2483 MAC settings required to run LoRa commands (join, tx, etc).
/*!
	Resets the software LoRaWAN stack and initialises all of the required parameters (set in 
	config.h) to communicate over a LoRaWAN network.

	@return RN2483_SUCCESS The function reset & initialised all the required values without failure
	@return RN2483_ERR_PARAM Likely means memory issue was caused while reading a response from the 
			RN2483
	@return RN2483_ERR_PANIC If this happens something went really wrong when writing a command
*/
int RN2483_initMAC();
//! Attempts to join a LoRa network using the specified mode.
/*!
	Sends out a request to join local LoRaWAN network in set mode, there are two responses from the 
    RN2483 (handled by this function), the first detirmines whether the command was correct, the 
    second detirmines whether the join request was successful.

    @see RN2483_JoinModes for valid mode values

    @return RN2483_ERR_PARAM Invalid mode parameter
    @return RN2483_ERR_PANIC Error reading response from the RN2384
    @return RN2483_ERR_KIDS Required keys & identifiers are not intialised
    @return RN2483_ERR_BUSY All configured frequency channels are currently busy, wait and try again
    @return RN2483_ERR_STATE Module cannot make join request in current state
    @return RN2483_DENIED Request went through, but the network denied your request
    @return RN2483_SUCCESS Successfully joined LoRaWAN network
*/
int RN2483_join(int mode);
//! Sends a confirmed/unconfirmed frame with an application payload of buff.
/*!
	TODO
*/
int RN2483_tx(const void *buff, bool confirm, char *downlink);

#endif // RN2483

