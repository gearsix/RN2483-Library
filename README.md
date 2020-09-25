# General-Platform RN2483 Library

A platform-independent embedded C library for the Micrchip RN2483 LoRa module.

**NOTE:** This repo is currently not maintained and was written against v1.0 of the LoRaWAN spec. Consider it depreciated _for now_.
Lemme know if you wanna 


## Contents

1. Overview
2. Documentation
4. Usage
5. Supported Platforms
6. Adding Platforms
7. Authors


## Overview

This is an embedded C library for interacting with the [Microchip RN2483](https://www.microchip.com/wwwproducts/en/RN2483) LoRa module. It aims to be simple and modular (enough to make porting it to different platforms easy).

One of the main features of this library is it's portability. An embedded library with any i/o can never be _truly_ portable, so specific platforms are supported in seperate branches of the repository.
The _master_ branch of this repo is the core platform-independent code.
The individual branches (e.g. `platform/mbit`), are what you'll actually want to use if youre trying to deploy this for use on a platform.

The only hardware-specific functionality requried by this library is the ability to R/W over UART to the RN2483 module. Consequently, this is handled by a wrapper functions: `read` and `write`.
In the _master_ branch, these are simply filled with #error that tells you to implement them on compilation.

**For details on adding support for a specific platform, see 6. AddingPlatforms**.

**For examples of specific platform support, see 5. Supported Platforms**.


## Documentation

**There is [Doxygen](http://www.stack.nl/~dimitri/doxygen/) documentation**, just run doxygen doxycfg in the main directory and it'll generate the docs/ folder. All the comments should be doxygen compatible and I've tried to be as thorough as possible, but I'll give a brief overview of it here for ease-of-use sake.

The library is written in standard C (C99) and provides full functionality of the RN2483 module.

There's a `command` function that allows you to write any valid command to the module (see the [Command Reference](http://ww1.microchip.com/downloads/en/DeviceDoc/40001784B.pdf) for valid commands)

There's an `initMAC` command that uses settings defined in the `rn2483.cfg` file (which gets written to `config.h` by _Makefile_) to initialise all the LoRaWAN-specific settings you need to successfully connect toa LoRaWAN network.

Aside from this, the other notable functions are `join` (join a network) and `tx` (transmit data over connected network), which handle the LoRaWAN handshake for you.

_Note: I am looking to expand this library in the future and tidy it up._


## Usage

**Make sure to check the rn2483.cfg file to configure your LoRaWAN settings and run the Makefile**

Setup is going to depend on your platform, so for that see the specific platform branch's README.
There's no init function or anything for setting up the pins to worry about - that's all done in the `read` and `write` functions (implemented by you, for your usecase).

In the _master_ branch, I initally had `printf` and `getc` functions for this (with the intention of letting the user reroute the stdin and stdout stream or redefine the functions with macros), but after experiencing the _BBC Micro:Bit's_ CMake build process I decided it's easier to just decided to just use wrapper functions that are modified for each platform.

Aside from setup, the general usage should go:

1. _RN2483_reset();_ = performs a hardware reset (toggles the RESET pin)
2. _RN2483_initMAC();_ = initialises all the keys & id's for your network (see rn2483.cfg)
3. _RN2483_join(mode);_ = join your LoRaWAN network in _mode_ (see RN2483_JoinModes in docs)
4. _RN2483_tx(buffer, true, downlink_buffer);_ = tx your data in confirmed/unconfirmed, recieve and downlink

**Remember that you can access any other functionality of the RN2483 through the RN2483_command() function**


## Supported Platforms

### BBC Micro:Bit
See branch: **platform/mbit**'s README.md.


## Adding Platforms

I've tried to modularise the changes needed to add a platform as much as possible. This is mostly done through the read/write wrapper functions in rn2483.c, but if you look at the BBC Micro:Bit branch you'll see that in some cases you'll need to change more than this (see that branch's README for details).

Functions that _need_ changing in `rn2483.c`:

- **rn2483.c/static uint8_t read()** = Read 1 byte from the UART line connected to the RN2483 module and return it.
- **rn2483.c/static void write(uint8_t \*buffer)** = This function simply writes buffer to over the UART line connected to the RN2483 module. This is usually done through a printf() function.

Obviously, it's never this simple, so you might run into some roadblocks that require further modifications.
For example, in the platform/mbit branch I had to pass around pointers to the MicroBit's Serial object.


## Authors

- Alexander Collins (alexander-collins@outlook.com)
