# Application Building Makefile

##############################################
################ APPLICATION #################
##############################################

# Application Flags
APPLICATION_CFLAGS    = $(GENERIC_CFLAGS)
APPLICATION_INCFLAGS  = -I$(APPLICATION_INCDIR)
APPLICATION_INCFLAGS += -I$(CORE_INCDIR)
APPLICATION_INCFLAGS += -I$(OS_KERNEL_INCDIR) -I$(OS_KERNEL_ARM_DIR) -I$(CONF_FREERTOS_DIR)
APPLICATION_INCFLAGS += -I$(GENERIC_HAL_INCDIR) -I$(HAL_INCDIR) -I$(HAL_INCDIR)/Legacy -I$(CONF_HALS_DIR)
APPLICATION_INCFLAGS += -I$(CMSIS_INCDIR) -I$(CMSIS_INCDIR_DEVICE)
APPLICATION_INCFLAGS += -I$(BSP_INCDIR)

# Application Files
APPLICATION_SRCS = $(wildcard $(APPLICATION_SRCDIR)/*.c $(APPLICATION_SRCDIR)/*/*.c)
APPLICATION_OBJS = $(subst $(APPLICATION_SRCDIR)/,$(BUILD_APPLICATION_DIR)/,$(APPLICATION_SRCS:.c=-$(VERSION).o))

# Application compilation
$(BUILD_APPLICATION_DIR)/%-$(VERSION).o : $(APPLICATION_SRCDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(APPLICATION_CFLAGS) $(APPLICATION_INCFLAGS) $(VERSION_FLAGS) $^ -o $@

application : $(APPLICATION_OBJS)
	@echo "**************************************"
	@echo "*****   Application Build Done   *****"
	@echo "**************************************"
	@echo