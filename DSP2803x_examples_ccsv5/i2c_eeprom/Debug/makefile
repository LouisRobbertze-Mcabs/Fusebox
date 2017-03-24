################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/c2000_6.2.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./Example_2803xI2C_eeprom.obj" \
"./DSP2803x_usDelay.obj" \
"./DSP2803x_SysCtrl.obj" \
"./DSP2803x_Spi.obj" \
"./DSP2803x_PieVect.obj" \
"./DSP2803x_PieCtrl.obj" \
"./DSP2803x_I2C.obj" \
"./DSP2803x_GlobalVariableDefs.obj" \
"./DSP2803x_ECan.obj" \
"./DSP2803x_DefaultIsr.obj" \
"./DSP2803x_CpuTimers.obj" \
"./DSP2803x_CodeStartBranch.obj" \
"./DSP2803x_Adc.obj" \
"C:/Users/Bartho/Documents/GitHub/BatteryBestuurStelsel/BatteryBestuurStelsel/DSP2803x_headers/cmd/DSP2803x_Headers_nonBIOS.cmd" \
"../F28035.cmd" \
"../IQmath.lib" \
-l"rts2800_ml.lib" \
-l"IQmath.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Example_2803xI2C_eeprom.out \

EXE_OUTPUTS__QUOTED += \
"Example_2803xI2C_eeprom.out" \


# All Target
all: Example_2803xI2C_eeprom.out

# Tool invocations
Example_2803xI2C_eeprom.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data -z -m"Example_2803xI2C_eeprom.map" --stack_size=0x380 --warn_sections -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/lib" -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -i"C:/Users/Bartho/Documents/GitHub/BatteryBestuurStelsel/BatteryBestuurStelsel/DSP2803x_examples_ccsv5/i2c_eeprom" -i"C:/Users/Bartho/Documents/GitHub/BatteryBestuurStelsel/BatteryBestuurStelsel/DSP2803x_common/lib" -i"C:/Users/Bartho/Documents/libs/math/IQmath/v160/lib" --reread_libs --verbose_diagnostics --issue_remarks --xml_link_info="Example_2803xI2C_eeprom_linkInfo.xml" --entry_point=code_start --rom_model -o "Example_2803xI2C_eeprom.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "DSP2803x_Adc.pp" "DSP2803x_CpuTimers.pp" "DSP2803x_DefaultIsr.pp" "DSP2803x_ECan.pp" "DSP2803x_GlobalVariableDefs.pp" "DSP2803x_I2C.pp" "DSP2803x_PieCtrl.pp" "DSP2803x_PieVect.pp" "DSP2803x_Spi.pp" "DSP2803x_SysCtrl.pp" "Example_2803xI2C_eeprom.pp" 
	-$(RM) "DSP2803x_Adc.obj" "DSP2803x_CodeStartBranch.obj" "DSP2803x_CpuTimers.obj" "DSP2803x_DefaultIsr.obj" "DSP2803x_ECan.obj" "DSP2803x_GlobalVariableDefs.obj" "DSP2803x_I2C.obj" "DSP2803x_PieCtrl.obj" "DSP2803x_PieVect.obj" "DSP2803x_Spi.obj" "DSP2803x_SysCtrl.obj" "DSP2803x_usDelay.obj" "Example_2803xI2C_eeprom.obj" 
	-$(RM) "DSP2803x_CodeStartBranch.pp" "DSP2803x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

