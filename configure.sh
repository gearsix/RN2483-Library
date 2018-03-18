#!/bin/sh
##
# Configuration file for LoRa RN2483 library on the BBC Micro:Bit
##

# The source directory of the target yotta module you need the library for
DIR_TARGET="/home/alex/Documents/uni/DSP/NEW/demo/src/"

# use pruned Makefile to generate inc/config.h
make

# function to move relevant files to DIR_TARGET
cp inc/* src/* $DIR_TARGET

