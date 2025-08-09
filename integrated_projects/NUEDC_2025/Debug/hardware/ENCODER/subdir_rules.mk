################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
hardware/ENCODER/%.o: ../hardware/ENCODER/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/NUEDC_2025/hardware/OLED" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/NUEDC_2025/hardware/MOTO" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/NUEDC_2025/hardware/LX225" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/NUEDC_2025/hardware/KEY" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/NUEDC_2025/hardware/ENCODER" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/NUEDC_2025/hardware/DELAY" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/NUEDC_2025/hardware/CTRL" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/NUEDC_2025" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/NUEDC_2025/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"hardware/ENCODER/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


