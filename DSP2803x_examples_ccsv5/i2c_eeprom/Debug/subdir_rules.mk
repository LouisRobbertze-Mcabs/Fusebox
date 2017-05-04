################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
DSP2803x_CodeStartBranch.obj: C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_CodeStartBranch.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_usDelay.obj: C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/source/DSP2803x_usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="DSP2803x_usDelay.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Main.obj: ../Main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="Main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

User_Functions.obj: ../User_Functions.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="User_Functions.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

User_Globals.obj: ../User_Globals.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_headers/include" --include_path="C:/Users/Sonja/Documents/GitHub/BatteryBestuurStelsel/DSP2803x_common/include" --include_path="C:/Users/Sonja/libs/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="User_Globals.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


