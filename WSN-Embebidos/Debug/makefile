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
all: WSN-Embebidos.axf

# Tool invocations
WSN-Embebidos.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/joaquin/Documentos/Embebidos/Repositorio/WSN-LSE/CMSISv2p00_LPC17xx/Debug" -L"/home/joaquin/Documentos/Embebidos/Repositorio/WSN-LSE/CMSISv2p10_DSPLIB_CM3/lib" -Xlinker -Map="WSN-Embebidos.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "WSN-Embebidos_Debug.ld" -o"WSN-Embebidos.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) WSN-Embebidos.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "WSN-Embebidos.axf"; # arm-none-eabi-objcopy -O binary "WSN-Embebidos.axf" "WSN-Embebidos.bin" ; checksum -p LPC1769 -d "WSN-Embebidos.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
