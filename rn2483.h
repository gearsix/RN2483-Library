/*
	DOC FILE HERE
*/

#ifndef RN2483
#define RN2483

//========
// MACROS
//========
//includes

//defines
#define RN2483_MAX_BUFF	250	//tmp; TODO count max response length

//=========
// GLOBALS
//=========
enum RN2483_JoinModes {
    RN2483_OTAA,
	RN2483_ABP
};

//===========
// FUNCTIONS
//===========
//system
int RN2483_reset();
int RN2483_autobaud();
int	RN2483_command(const char *command, char *response);
int RN2483_firmware(char *buff);

//LoRa
int RN2483_initMAC();
int RN2483_join(int mode);
int RN2483_tx(const uint8_t *buff, bool confirm);

#endif // RN2483

