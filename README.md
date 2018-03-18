# TODO

# LoRa RN2483 Library
## platform/bbc-microbit-classic
Since the BBC Micro:Bit yotta build obscures a lot of the build process from the user, it's easier to just copy the source and header files into your yotta module source/ directory and include them directly.
I've written a small script to generate the config.h and do this (you'll need to provide the target module/source/ directory).

I've tried adding the .a as an dependency in a .cmake file (http://docs.yottabuild.org/reference/buildsystem.html#custom-cmake), I've tried the "extraIncludes" field in the module.json, **honestly this is just easier**.

This branch is going to have all the changes to the library I've had to make for the BBC MicroBit.