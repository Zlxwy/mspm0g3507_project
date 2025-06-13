################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
模仿STM32/%.o: ../模仿STM32/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccstheia150/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/TI/ccs_project/workspace_example/iic_hardware_oled_simple_display" -I"D:/TI/ccs_project/workspace_example/iic_hardware_oled_simple_display/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -I"D:/TI/ccs_project/workspace_example/iic_hardware_oled_simple_display/imitateSTM32" -I"D:/TI/ccs_project/workspace_example/iic_hardware_oled_simple_display/oled" -gdwarf-3 -MMD -MP -MF"模仿STM32/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


