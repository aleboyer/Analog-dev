################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
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
all: Analog-dev.axf

# Tool invocations
Analog-dev.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C++ Linker'
	arm-none-eabi-g++ -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "Analog-dev.ld" --specs=nosys.specs -Xlinker --gc-sections -Xlinker -Map="Analog-dev.map" -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o Analog-dev.axf "./CMSIS/EFM32WG/startup_efm32wg.o" "./CMSIS/EFM32WG/system_efm32wg.o" "./emlib/em_cmu.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./src/epsilometer_analog.o" "./src/epsilometer_coms.o" "./src/epsilometer_main.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: Analog-dev.hex'
	arm-none-eabi-objcopy -O ihex "Analog-dev.axf" "Analog-dev.hex"
	@echo ' '

	@echo 'Building bin file: Analog-dev.bin'
	arm-none-eabi-objcopy -O binary "Analog-dev.axf" "Analog-dev.bin"
	@echo ' '

	@echo 'Building s37 file: Analog-dev.s37'
	arm-none-eabi-objcopy -O srec "Analog-dev.axf" "Analog-dev.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "Analog-dev.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) Analog-dev.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
