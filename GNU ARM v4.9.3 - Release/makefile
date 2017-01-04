################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include ff12b/src/option/subdir.mk
-include ff12b/src/subdir.mk
-include emlib/subdir.mk
-include Calendar/subdir.mk
-include CMSIS/EFM32WG/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Epsilometer_v1.axf

# Tool invocations
Epsilometer_v1.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C++ Linker'
	arm-none-eabi-g++ -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "Epsilometer_v1.ld" --specs=nosys.specs -Xlinker --gc-sections -Xlinker -Map="Epsilometer_v1.map" -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o Epsilometer_v1.axf "./CMSIS/EFM32WG/startup_efm32wg.o" "./CMSIS/EFM32WG/system_efm32wg.o" "./Calendar/clock_tc.o" "./Calendar/crystal_parameters.o" "./Calendar/main_calendar_tc.o" "./emlib/em_cmu.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_rtc.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./ff12b/src/diskio.o" "./ff12b/src/ff.o" "./ff12b/src/option/ccsbcs.o" "./src/epsilometer_analog.o" "./src/epsilometer_coms.o" "./src/epsilometer_main.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: Epsilometer_v1.hex'
	arm-none-eabi-objcopy -O ihex "Epsilometer_v1.axf" "Epsilometer_v1.hex"
	@echo ' '

	@echo 'Building bin file: Epsilometer_v1.bin'
	arm-none-eabi-objcopy -O binary "Epsilometer_v1.axf" "Epsilometer_v1.bin"
	@echo ' '

	@echo 'Building s37 file: Epsilometer_v1.s37'
	arm-none-eabi-objcopy -O srec "Epsilometer_v1.axf" "Epsilometer_v1.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "Epsilometer_v1.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) Epsilometer_v1.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
