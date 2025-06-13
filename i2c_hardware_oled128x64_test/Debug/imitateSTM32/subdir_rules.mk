################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
imitateSTM32/%.o: ../imitateSTM32/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccstheia150/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/MCU/TI/ccs_project/mspm0g3507/workspace_example/i2c_hardware_oled128x64_test" -I"D:/MCU/TI/ccs_project/mspm0g3507/workspace_example/i2c_hardware_oled128x64_test/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -I"D:/MCU/TI/ccs_project/mspm0g3507/workspace_example/i2c_hardware_oled128x64_test/hardware/oled" -gdwarf-3 -MMD -MP -MF"imitateSTM32/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


