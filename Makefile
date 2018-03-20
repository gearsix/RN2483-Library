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
DIR_INC	= inc/

#
# BUILD
#
.PHONY: all
all: init inc/config.h

.SILENT: init
init:
	$(RM) inc/config.h

#
# DEPENDENCIES
#
# rn2483.cfg to a C header file (inc/config.h)
.SILENT: inc/config.h
inc/config.h: rn2483.cfg
	$(info Writing rn2483 configuration...)
	$(ECHO)	"/*!"															>> $@
	$(ECHO)	"    @file config.h"											>> $@
	$(ECHO)	"    @author Alexander Collins (alexnader-collins@outlook.com"	>> $@
	$(ECHO)	"    @date September 2017 - April 2018"							>> $@
	$(ECHO)	"    @brief configuration file generated from rn2483.cfg"		>> $@
	$(ECHO)	"*/"															>> $@
	$(ECHO)	""																>> $@
	$(ECHO) "#ifndef RN2483_CONFIG"											>> $@
	$(ECHO) "#define RN2483_CONFIG"											>> $@
	$(ECHO) ""																>> $@
	$(ECHO) "#define LoRaWAN_Frequency \"$(cfg_Frequency)\""				>> $@
	$(ECHO) ""																>> $@
	$(ECHO) "#define LoRaWAN_DevAddr \"$(cfg_DevAddr)\""					>> $@
	$(ECHO) "#define LoRaWAN_DevEUI  \"$(cfg_DevEUI)\""						>> $@
	$(ECHO) "#define LoRaWAN_AppEUI  \"$(cfg_AppEUI)\""						>> $@
	$(ECHO) "#define LoRaWAN_AppKey  \"$(cfg_AppKey)\""						>> $@
	$(ECHO) "#define LoRaWAN_NwkSKey \"$(cfg_NwkSKey)\""					>> $@
	$(ECHO) "#define LoRaWAN_AppSKey \"$(cfg_AppSKey)\""					>> $@
	$(ECHO) ""																>> $@
	$(ECHO) "#define LoRaWAN_JoinMode \"$(cfg_JoinMode)\""					>> $@
	$(ECHO) ""																>> $@
	$(ECHO) "#define LoRaWAN_DataRate \"$(cfg_DataRate)\""					>> $@
	$(ECHO) ""																>> $@
	$(ECHO) "#define LoRaWAN_ADR \"$(cfg_ADR)\""							>> $@
	$(ECHO) ""																>> $@
	$(ECHO) "#define LoRaWAN_Port \"$(cfg_Port)\""							>> $@
	$(ECHO) "#endif // RN2483_CONFIG"										>> $@
	$(ECHO) ""																>> $@

