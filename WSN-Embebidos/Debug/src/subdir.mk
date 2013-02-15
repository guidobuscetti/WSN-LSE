################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cc2520-mac.c \
../src/cc2520.c \
../src/cr_startup_lpc176x.c \
../src/fijo.c \
../src/hiduser.c \
../src/main.c \
../src/movil.c \
../src/rssi.c \
../src/usbcore.c \
../src/usbdesc.c \
../src/usbhw.c \
../src/usbuser.c 

OBJS += \
./src/cc2520-mac.o \
./src/cc2520.o \
./src/cr_startup_lpc176x.o \
./src/fijo.o \
./src/hiduser.o \
./src/main.o \
./src/movil.o \
./src/rssi.o \
./src/usbcore.o \
./src/usbdesc.o \
./src/usbhw.o \
./src/usbuser.o 

C_DEPS += \
./src/cc2520-mac.d \
./src/cc2520.d \
./src/cr_startup_lpc176x.d \
./src/fijo.d \
./src/hiduser.d \
./src/main.d \
./src/movil.d \
./src/rssi.d \
./src/usbcore.d \
./src/usbdesc.d \
./src/usbhw.d \
./src/usbuser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__USE_CMSIS_DSPLIB=CMSISv2p10_DSPLIB_CM3 -I"C:\Users\Joaquin\Documents\Joaquin\Facu\Materias\Sistemas Embebidos\Proyecto\Repositorio\WSN-LSE\WSN-Embebidos\src" -I"C:\Users\Joaquin\Documents\Joaquin\Facu\Materias\Sistemas Embebidos\Proyecto\Repositorio\WSN-LSE\CMSISv2p00_LPC17xx\inc" -I"C:\Users\Joaquin\Documents\Joaquin\Facu\Materias\Sistemas Embebidos\Proyecto\Repositorio\WSN-LSE\CMSISv2p10_DSPLIB_CM3\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc176x.o: ../src/cr_startup_lpc176x.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__USE_CMSIS_DSPLIB=CMSISv2p10_DSPLIB_CM3 -I"C:\Users\Joaquin\Documents\Joaquin\Facu\Materias\Sistemas Embebidos\Proyecto\Repositorio\WSN-LSE\WSN-Embebidos\src" -I"C:\Users\Joaquin\Documents\Joaquin\Facu\Materias\Sistemas Embebidos\Proyecto\Repositorio\WSN-LSE\CMSISv2p00_LPC17xx\inc" -I"C:\Users\Joaquin\Documents\Joaquin\Facu\Materias\Sistemas Embebidos\Proyecto\Repositorio\WSN-LSE\CMSISv2p10_DSPLIB_CM3\inc" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc176x.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


