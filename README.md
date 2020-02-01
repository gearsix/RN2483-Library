# General-Platform RN2483 Library
A non-platform-specific embedded C library for the Micrchip RN2483 LoRa module.

**NOTE:** This repo is currently not maintained and was written against v1.0 of the LoRaWAN spec. Until it validated/updated it, you should probably consider it depreciated.

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

Setup is going to depend on your platform, so for that see the specific platform branch's README.

There's no init function or anything for setting up the pins, instead how the library communiates to the module is detirmed by the specific branches.

In the _master_ branch, I initally had printf and getc functions for this (with the intention of letting the user reroute the stdin and stdout stream or redefine the functions with macros), but after experiencing the BBC Micro:Bit's CMake build process I decided it's easier to just decided to just use wrapper functions that are modified in each branch.

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
