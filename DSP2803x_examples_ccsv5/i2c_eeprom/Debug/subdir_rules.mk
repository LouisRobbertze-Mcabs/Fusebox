################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
DSP2803x_Adc.obj: C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_Adc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_Adc.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_CodeStartBranch.obj: C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_CodeStartBranch.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_CpuTimers.obj: C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_CpuTimers.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_CpuTimers.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_DefaultIsr.obj: C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_DefaultIsr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_DefaultIsr.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_ECan.obj: ../DSP2803x_ECan.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_ECan.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_GlobalVariableDefs.obj: C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/source/DSP2803x_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_GlobalVariableDefs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_I2C.obj: C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_I2C.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_I2C.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_PieCtrl.obj: C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_PieCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_PieCtrl.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_PieVect.obj: C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_PieVect.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_PieVect.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_Spi.obj: C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_Spi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_Spi.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_SysCtrl.obj: C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_SysCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_SysCtrl.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_usDelay.obj: C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_usDelay.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Example_2803xI2C_eeprom.obj: ../Example_2803xI2C_eeprom.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="Example_2803xI2C_eeprom.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


