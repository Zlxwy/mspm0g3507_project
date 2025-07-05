################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
hardware/decoder/%.o: ../hardware/decoder/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/hc595" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/decoder" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/LEDMatrix" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/delay" -gdwarf-3 -MMD -MP -MF"hardware/decoder/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


