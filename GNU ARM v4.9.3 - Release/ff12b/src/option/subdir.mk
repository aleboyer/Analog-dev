################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ff12b/src/option/ccsbcs.c 

OBJS += \
./ff12b/src/option/ccsbcs.o 

C_DEPS += \
./ff12b/src/option/ccsbcs.d 


# Each subdirectory must supply rules for building sources it contributes
ff12b/src/option/ccsbcs.o: ../ff12b/src/option/ccsbcs.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DEFM32WG842F256=1' '-DNDEBUG=1' -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32WG/Include" -I"/Users/epsi-user/SimplicityStudio/v4_workspace/Epsilometer_v1/inc" -I"/Users/epsi-user/SimplicityStudio/v4_workspace/Epsilometer_v1/ff12b/src" -I"/Users/epsi-user/SimplicityStudio/v4_workspace/Epsilometer_v1/Calendar" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"ff12b/src/option/ccsbcs.d" -MT"ff12b/src/option/ccsbcs.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


