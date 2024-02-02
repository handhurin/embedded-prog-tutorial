# Makefile with verification rules

##############################################
################ CHECKER FILES ###############
##############################################

CHECKER_SRCS =	$(CORE_SRCS)

CHECKER_INCS =	-I$(CORE_INCDIR)

##############################################
############### CHECKER CONFIGS ##############
##############################################

CHECKER_CMDS  = --enable=all # Enables all warnings
CHECKER_CMDS += --suppress=missingInclude # Disables missing include warnings
CHECKER_CMDS += --suppress=unusedFunction # Disables unused function warnings
CHECKER_CMDS += --inline-suppr # Allows to do suppress inside the code (inline)
CHECKER_CMDS += --addon=$(CONF_MISRA_DIR)/misra.json # Check MISRA C compliancee if misra settings are added 
CHECKER_CMDS += --output-file=build/code-checking.log # Print the result in a log file 
CHECKER_CMDS += --error-exitcode=1 # Returns 1 if cppcheck has encountered an error

##############################################
############## CHECKER COMMANDS ##############
##############################################

CHECKER_ERROR_MSG = "\033[1;31mCode checked: errors have been found. Please correct them before continuing.\033[0m"

.PHONY += verif

verif :
	@mkdir -p $(BUILD_DIR)
	@$(CHECKER) $(CHECKER_CMDS) -D$(CHIP) -D$(BOARD) $(CHECKER_INCS) $(CHECKER_SRCS) || (cat build/code-checking.log; echo $(CHECKER_ERROR_MSG) ; exit 1)
	