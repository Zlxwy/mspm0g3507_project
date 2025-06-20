################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/gpio_i2c_simulator_oled_driver/hardware/delay" -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/gpio_i2c_simulator_oled_driver/hardware/OLED" -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/gpio_i2c_simulator_oled_driver" -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/gpio_i2c_simulator_oled_driver/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1590906817: ../main.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.20.0/sysconfig_cli.bat" --script "E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/gpio_i2c_simulator_oled_driver/main.syscfg" -o "." -s "C:/ti/mspm0_sdk_2_01_00_03/.metadata/product.json" -d "MSPM0G350X" -p "LQFP-48(PT)" -r "Default" --context "system" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1590906817 ../main.syscfg
device.opt: build-1590906817
device.cmd.genlibs: build-1590906817
ti_msp_dl_config.c: build-1590906817
ti_msp_dl_config.h: build-1590906817
Event.dot: build-1590906817

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/gpio_i2c_simulator_oled_driver/hardware/delay" -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/gpio_i2c_simulator_oled_driver/hardware/OLED" -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/gpio_i2c_simulator_oled_driver" -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/gpio_i2c_simulator_oled_driver/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/ti/mspm0_sdk_2_01_00_03/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/gpio_i2c_simulator_oled_driver/hardware/delay" -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/gpio_i2c_simulator_oled_driver/hardware/OLED" -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/gpio_i2c_simulator_oled_driver" -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/gpio_i2c_simulator_oled_driver/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


