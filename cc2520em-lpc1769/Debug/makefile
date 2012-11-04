################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: cc2520em-lpc1769.axf

# Tool invocations
cc2520em-lpc1769.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/joaquin/Documentos/Embebidos/workspace_proyecto1/CMSISv2p00_LPC17xx/Debug" -Xlinker -Map="cc2520em-lpc1769.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "cc2520em-lpc1769_Debug.ld" -o"cc2520em-lpc1769.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) cc2520em-lpc1769.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "cc2520em-lpc1769.axf"; # arm-none-eabi-objcopy -O binary "cc2520em-lpc1769.axf" "cc2520em-lpc1769.bin" ; checksum -p LPC1769 -d "cc2520em-lpc1769.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
