################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/cmd/DSP2803x_Headers_nonBIOS.cmd \
../F28035.cmd 

LIB_SRCS += \
../IQmath.lib 

ASM_SRCS += \
C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_CodeStartBranch.asm \
C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_usDelay.asm 

C_SRCS += \
C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_Adc.c \
C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_CpuTimers.c \
C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_DefaultIsr.c \
../DSP2803x_ECan.c \
C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/source/DSP2803x_GlobalVariableDefs.c \
C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_I2C.c \
C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_PieCtrl.c \
C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_PieVect.c \
C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_Spi.c \
C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_SysCtrl.c \
../Example_2803xI2C_eeprom.c 

C_DEPS += \
./DSP2803x_Adc.d \
./DSP2803x_CpuTimers.d \
./DSP2803x_DefaultIsr.d \
./DSP2803x_ECan.d \
./DSP2803x_GlobalVariableDefs.d \
./DSP2803x_I2C.d \
./DSP2803x_PieCtrl.d \
./DSP2803x_PieVect.d \
./DSP2803x_Spi.d \
./DSP2803x_SysCtrl.d \
./Example_2803xI2C_eeprom.d 

OBJS += \
./DSP2803x_Adc.obj \
./DSP2803x_CodeStartBranch.obj \
./DSP2803x_CpuTimers.obj \
./DSP2803x_DefaultIsr.obj \
./DSP2803x_ECan.obj \
./DSP2803x_GlobalVariableDefs.obj \
./DSP2803x_I2C.obj \
./DSP2803x_PieCtrl.obj \
./DSP2803x_PieVect.obj \
./DSP2803x_Spi.obj \
./DSP2803x_SysCtrl.obj \
./DSP2803x_usDelay.obj \
./Example_2803xI2C_eeprom.obj 

ASM_DEPS += \
./DSP2803x_CodeStartBranch.d \
./DSP2803x_usDelay.d 

OBJS__QUOTED += \
"DSP2803x_Adc.obj" \
"DSP2803x_CodeStartBranch.obj" \
"DSP2803x_CpuTimers.obj" \
"DSP2803x_DefaultIsr.obj" \
"DSP2803x_ECan.obj" \
"DSP2803x_GlobalVariableDefs.obj" \
"DSP2803x_I2C.obj" \
"DSP2803x_PieCtrl.obj" \
"DSP2803x_PieVect.obj" \
"DSP2803x_Spi.obj" \
"DSP2803x_SysCtrl.obj" \
"DSP2803x_usDelay.obj" \
"Example_2803xI2C_eeprom.obj" 

C_DEPS__QUOTED += \
"DSP2803x_Adc.d" \
"DSP2803x_CpuTimers.d" \
"DSP2803x_DefaultIsr.d" \
"DSP2803x_ECan.d" \
"DSP2803x_GlobalVariableDefs.d" \
"DSP2803x_I2C.d" \
"DSP2803x_PieCtrl.d" \
"DSP2803x_PieVect.d" \
"DSP2803x_Spi.d" \
"DSP2803x_SysCtrl.d" \
"Example_2803xI2C_eeprom.d" 

ASM_DEPS__QUOTED += \
"DSP2803x_CodeStartBranch.d" \
"DSP2803x_usDelay.d" 

C_SRCS__QUOTED += \
"C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_Adc.c" \
"C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_CpuTimers.c" \
"C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_DefaultIsr.c" \
"../DSP2803x_ECan.c" \
"C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/source/DSP2803x_GlobalVariableDefs.c" \
"C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_I2C.c" \
"C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_PieCtrl.c" \
"C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_PieVect.c" \
"C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_Spi.c" \
"C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_SysCtrl.c" \
"../Example_2803xI2C_eeprom.c" 

ASM_SRCS__QUOTED += \
"C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_CodeStartBranch.asm" \
"C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_usDelay.asm" 


