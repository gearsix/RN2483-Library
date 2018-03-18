########################################
# RN2483 Library Makefile
# author:	alexander collins
# date:		September 2017 - April 2018
########################################
#
# EXTERNAL
#
include rn2483.cfg  #cfg_*

#
# CONSTANTS
#
# system
RM		= rm -f
ECHO	= echo
# compiler
CC		= $(cfg_COMPILER)
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
all: inc/config.h $(TARGET) clean

$(TARGET): $(OBJECTS)
	$(AR) $(TARGET) $(OBJECTS)

$(OBJECTS): $(SOURCES)
	$(CC) -c $(SOURCES) $(FLAGS) $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(OBJECTS)

#
# DEPENDENCIES
#
# rn2483.cfg to a C header file (inc/config.h)
.SILENT: inc/config.h
inc/config.h: rn2483.cfg
	$(info Writing rn2483 configuration...)
	$(RM) $@
	$(ECHO) "#ifndef RN2483_CONFIG"								>> $@
	$(ECHO) "#define RN2483_CONFIG"								>> $@
	$(ECHO) ""													>> $@
	$(ECHO) "#define LoRaWAN_Frequency \"$(cfg_Frequency)\""	>> $@
	$(ECHO) ""													>> $@
	$(ECHO) "#define LoRaWAN_DevAddr \"$(cfg_DevAddr)\""		>> $@
	$(ECHO) "#define LoRaWAN_DevEUI  \"$(cfg_DevEUI)\""			>> $@
	$(ECHO) "#define LoRaWAN_AppEUI  \"$(cfg_AppEUI)\""			>> $@
	$(ECHO) "#define LoRaWAN_AppKey  \"$(cfg_AppKey)\""			>> $@
	$(ECHO) ""													>> $@
	$(ECHO) "#define LoRaWAN_JoinMode \"$(cfg_JoinMode)\""		>> $@
	$(ECHO) ""													>> $@
	$(ECHO) "#define LoRaWAN_DataRate \"$(cfg_DataRate)\""		>> $@
	$(ECHO) ""													>> $@
	$(ECHO) "#define LoRaWAN_Port \"$(cfg_Port)\""				>> $@
	$(ECHO) "#endif // RN2483_CONFIG"							>> $@

