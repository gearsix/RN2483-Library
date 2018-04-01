//========
// MACROS
//========
//includes
#include "MicroBit.h"
#include "microimg/MicroIMG.h"
#include "rn2483/rn2483.h"
//defines
#define RN2483TX    MICROBIT_PIN_P12
#define RN2483RX    MICROBIT_PIN_P8

//=========
// GLOBALS
//=========
//microbit
MicroBit uBit;
MicroBitSerial serial(USBTX, USBRX, RN2483_MAX_BUFF);
MicroBitPin RN2483_PIN_RESET(MICROBIT_ID_IO_P2, MICROBIT_PIN_P2, PIN_CAPABILITY_DIGITAL);
//general
char buffer[RN2483_MAX_BUFF];
int ret = -1;

//============
// PROTOTYPES
//============
void init();
void exit();
void configureSerial(PinName TX, PinName RX, int baud);
void debugPrint(const char *buffer);

//======
// MAIN
//======
int main()
{
    int tries = 0;

//init mbit
    init();

//init rn2483
    uBit.display.print("1");
    uBit.sleep(1000);

    configureSerial(RN2483TX, RN2483RX, 57600);
    if (RN2483_reset(&serial, &RN2483_PIN_RESET) != RN2483_SUCCESS)
    {
        uBit.display.print(MicroIMG_cross);
        debugPrint("reset failed\r\n");
        goto ERROR_EXIT;
    } 
    if (RN2483_initMAC(&serial) != RN2483_SUCCESS)
    {
        uBit.display.print(MicroIMG_cross);
        debugPrint("initMAC failed\r\n");
        goto ERROR_EXIT;
    }

    uBit.display.print(MicroIMG_tick);
    uBit.sleep(1000);
    uBit.display.clear();

//join
    uBit.display.print("2");
    uBit.sleep(1000);

    do {
        tries++;
        ret = RN2483_join(&serial, RN2483_ABP);
    } while (ret != RN2483_SUCCESS && tries < 5);

    if (ret == RN2483_SUCCESS)
        uBit.display.print(MicroIMG_tick);
    else
    {
        uBit.display.print(MicroIMG_cross);
        debugPrint("join failed\r\n");
        goto ERROR_EXIT;
    }

    uBit.sleep(1000);

//tx (if joined)
    if (ret == RN2483_SUCCESS)
    {
        uBit.display.print("3");
        uBit.sleep(1000);

        ret = RN2483_tx(&serial, "hello", true, buffer);
        if (ret == RN2483_SUCCESS || ret == RN2483_NODOWN)
        {
            uBit.display.print(MicroIMG_tick);
            uBit.sleep(1000);

            if (buffer[0] != '\0')
            {
                uBit.display.scroll(buffer);
                debugPrint(buffer);
            }
        }
        else
            uBit.display.print(MicroIMG_cross);
    }

//exit
    exit();
    return EXIT_SUCCESS;
ERROR_EXIT:
    debugPrint("ERROR_EXIT\r\n");
    return EXIT_FAILURE;
}

//===========
// FUNCTIONS
//===========
void init()
{
    // init MicroBit
    uBit.init();
    // print ready messages
    uBit.serial.printf("RDY\r\n");
    uBit.display.scroll("RDY", 50);
}
void exit()
{
    // print gdbye messages
    configureSerial(USBTX, USBRX, 115200);
    uBit.serial.printf("BYE\r\n");
    uBit.display.scroll("BYE", 50);
    // exit MicroBit
    release_fiber();
}
void configureSerial(PinName TX, PinName RX, int baud)
{
    serial.redirect(TX, RX);
    uBit.sleep(1000);
    serial.baud(baud);
    uBit.sleep(1000);
}
void debugPrint(const char *buffer)
{
    configureSerial(USBTX, USBRX, 115200);
    uBit.serial.printf("%s", buffer);
    uBit.serial.printf("\r\n");
    configureSerial(RN2483TX, RN2483RX, 9600);
}

