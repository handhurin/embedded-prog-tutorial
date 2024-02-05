# Principal Makefile

##############################################
################## PROJECT ###################
##############################################

PROJ_NAME = exercice-3
BOARD = NUCLEO_H745ZI
LOAD_MEMORY = flash
VERSION = debug

##############################################
################### MAKE #####################
##############################################

.PHONY = all clean echoes

all : clean build upload

include conf/settings.mk
include conf/path.mk
include conf/build.mk
include conf/debug.mk
include conf/code_verification.mk

clean :
	rm -rf $(BUILD_DIR)

echoes :
	@echo $(PROJ_NAME)
