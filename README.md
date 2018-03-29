# General-Platform RN2483 Library
A non-platform-specific embedded C library for the Micrchip RN2483 LoRa module.
**Specifc platforms are supported on seperate branches!**

## Contents
1. Overview
2. Documentation
4. Usage
5. Supported Platforms
6. Adding Platforms
7. Authors

## Overview
This is an embedded C library for interacting with the [Microchip RN2483](https://www.microchip.com/wwwproducts/en/RN2483) LoRa module. It's aim is to be as flexible as possible (not targeting specific hardware) and modular enough to make porting it to hardware very easy.

One of the main features of this library is it's portability. Obviously an embedded library can never be _truly_ portable, so instead there are several versions of the library for specific platforms that are managed through git branching. The _master_ branch of this repo is non-targeting that every other branch is derived from. The individual branches (e.g. platform/mbit), are what you'll actually want to use if you''re trying to deploy this framework and use it on a platform.

The only hardware-specific functionality requried by this library is the ability to R/W over UART to the RN2483 module. Consequently, this is handled by a wrapper ```read``` function and wrapper ```write``` function. In the non-platform specific _master_ branch, these are simply filled with #error.

**For details on adding support for a specific platform, see 6. AddingPlatforms**.

**For examples of specific platform support, see 5. Supported Platforms**.


## Documentation
**There is [Doxygen](http://www.stack.nl/~dimitri/doxygen/) documentation**, just run doxygen doxycfg in the main directory and it'll generate the docs/ folder. All the comments should be doxygen compatible and I've tried to be as thorough as possible, but I'll give a brief overview of it here for ease-of-use sake.

The library is pretty standard for a C library, and gives full access to the RN2843 (provided you've connected it right). 

There's a ```command``` function that allows you to write any valid command to the module (see the [Command Reference](http://ww1.microchip.com/downloads/en/DeviceDoc/40001784B.pdf) for valid commands)

There's an ```initMAC``` command that uses settings defined in the ```rn2483.cfg``` file (which gets written to ```config.h``` in the Makefile) to initialise all the LoRaWAN-specific stuff you'll need to successfully connect toa LoRaWAN network.

Aside from this, the other notable functions are obviously the ```join``` and ```tx```, which handle the multiple responses from the module for you.

_Note: I am looking to expand this library in the future and tidy it up. Possibly port it to C++ too._

## Usage
**Make sure to check the rn2483.cfg file to configure your LoRaWAN settings and run the Makefile**

**In the future I might change this branch so that instead of passing around a pointer to the uBit's serial object, you simply set a pointer at the start of your main**

For now, you need to just make sure you pass your uBit's serial object to each function, like so: ```&uBit.serial``` wherever it asks for a ```MicroBitSerial *``` parameter.

The other thing you'll need to make sure to do is set the uBit's serial to the RN2483, it makes debugging a nightamre since the uBit can only have 1 active Serial instance (even if you create several objects) - for reliability's sake it's easiest to simply set the baud and redirect the uBit.serial. This can be done by:
1. ```uBit.init()```
2. ```uBit.serial.redirect(RN2483_TX_PIN, RN2483_RX_PIN);```
3. ```uBit.serial.baud(57600);	//57600 is the RN2483's default baud rate```

Aside from setup, the general usage should go:
1. ```RN2483_reset(); //performs a hardware reset by toggling the RESET pin```
2. ```RN2483_initMAC(); //initialises all the keys & id's for your network (see rn2483.cfg)```
3. ```RN2483_join(mode); //join your LoRaWAN network in whatever mode (see RN2483_JoinModes in docs)```
4. ```RN2483_tx(buffer, true, downlink_buffer);	//tx your data in confirmed/unconfirmed and recieve and downlink```

**Remember that you can access any other functionality of the RN2483 through the RN2483_command() function**


## Supported Platforms
### BBC Micro:Bit
See branch: **platform/mbit**'s README.md.


## Adding Platforms
I've tried to modularise the changes needed to add a platform as much as possible. This is mostly done through the read/write wrapper functions in rn2483.c, but if you look at the BBC Micro:Bit branch you'll see that in some cases you'll need to change more than this (see that branch's README for details).

Functiosn that need changing in ```rn2483.c```:

##### ```rn2483.c/static uint8_t read()```

This function simply reads 1 byte from the UART line connected to the RN2483 module and returns it. Pretty simply.

##### ```rn2483.c/static void write(uint8_t *buffer)```

This function simply writes buffer to over the UART line connected to the RN2483 module. This is usually done through a printf() function.

#### other
Obviously, it's never this simple (although if you're lucky and how low enough level access it might be). So you might need to do more modifications. For example, in the platform/mbit branch I had to pass around pointers to the MicroBit's Serial object.


## Authors
- Alexander Collins (alexander-collins@outlook.com)
=======
# TODO

# LoRa RN2483 Library
## platform/bbc-microbit-classic
Since the BBC Micro:Bit yotta build obscures a lot of the build process from the user, it's easier to just copy the source and header files into your yotta module source/ directory and include them directly.
I've written a small script to generate the config.h and do this (you'll need to provide the target module/source/ directory).

I've tried adding the .a as an dependency in a .cmake file (http://docs.yottabuild.org/reference/buildsystem.html#custom-cmake), I've tried the "extraIncludes" field in the module.json, **honestly this is just easier**.

This branch is going to have all the changes to the library I've had to make for the BBC MicroBit.
>>>>>>> Decided I'll need to implement the lib into microbit demo like this :(
