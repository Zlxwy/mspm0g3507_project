################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
hardware/delay/%.o: ../hardware/delay/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/Controller/TI/ccs_project/mspm0g3507_project/peripheral_examples/timer_qei_encoder_measurement/hardware/OLED" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/peripheral_examples/timer_qei_encoder_measurement/hardware/delay" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/peripheral_examples/timer_qei_encoder_measurement" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/peripheral_examples/timer_qei_encoder_measurement/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"hardware/delay/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


