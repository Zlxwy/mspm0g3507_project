################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
hardware/OLED/%.o: ../hardware/OLED/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/uart_rx_dma_read_jy901s_data/hardware/OLED" -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/uart_rx_dma_read_jy901s_data/hardware/delay" -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/uart_rx_dma_read_jy901s_data" -I"E:/Controller/TI/ccs_project/mspm0g3507/workspace_examples/uart_rx_dma_read_jy901s_data/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"hardware/OLED/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


