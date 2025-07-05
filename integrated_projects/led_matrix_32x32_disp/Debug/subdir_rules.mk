################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/hc595" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/decoder" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/LEDMatrix" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/delay" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1279472319: ../main.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.20.0/sysconfig_cli.bat" --script "E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/main.syscfg" -o "." -s "C:/ti/mspm0_sdk_2_01_00_03/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1279472319 ../main.syscfg
device.opt: build-1279472319
device.cmd.genlibs: build-1279472319
ti_msp_dl_config.c: build-1279472319
ti_msp_dl_config.h: build-1279472319
Event.dot: build-1279472319

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/hc595" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/decoder" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/LEDMatrix" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/delay" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/ti/mspm0_sdk_2_01_00_03/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/hc595" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/decoder" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/LEDMatrix" -I"E:/Controller/TI/ccs_project/mspm0g3507_project/integrated_projects/led_matrix_32x32_disp/hardware/delay" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


