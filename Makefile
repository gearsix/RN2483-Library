########################################
# RN2483 Library Makefile
# author:	alexander collins
# date:		September 2017 - April 2018
########################################
#
# CONSTANTS
#
# system
RM		= rm -f
ECHO	= echo
# compiler
CC		= arm-none-eabi-gcc
AR		= ar rcs
# files
TARGET	= rn2483.a
DIR_INC	= inc/
SOURCES	= src/*.c
OBJECTS	= *.o
# flags
FLAGS	= -I$(DIR_INC)
CFLAGS	= -pedantic -Wall -Wextra

#
# BUILD
#
.PHONY: all
all: $(TARGET) clean

$(TARGET): $(OBJECTS)
	$(AR) $(TARGET) $(OBJECTS)

$(OBJECTS): $(SOURCES)
	$(CC) -c $(SOURCES) $(FLAGS) $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(OBJECTS)

