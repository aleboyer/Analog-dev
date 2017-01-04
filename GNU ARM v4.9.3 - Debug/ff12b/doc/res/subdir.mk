################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ff12b/doc/res/app1.c \
../ff12b/doc/res/app2.c \
../ff12b/doc/res/app3.c \
../ff12b/doc/res/app4.c 

OBJS += \
./ff12b/doc/res/app1.o \
./ff12b/doc/res/app2.o \
./ff12b/doc/res/app3.o \
./ff12b/doc/res/app4.o 

C_DEPS += \
./ff12b/doc/res/app1.d \
./ff12b/doc/res/app2.d \
./ff12b/doc/res/app3.d \
./ff12b/doc/res/app4.d 


# Each subdirectory must supply rules for building sources it contributes
ff12b/doc/res/app1.o: ../ff12b/doc/res/app1.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DEFM32WG842F256=1' '-DDEBUG=1' -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32WG/Include" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/emlib" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/inc" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/src" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/ff12b/src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"ff12b/doc/res/app1.d" -MT"ff12b/doc/res/app1.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ff12b/doc/res/app2.o: ../ff12b/doc/res/app2.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DEFM32WG842F256=1' '-DDEBUG=1' -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32WG/Include" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/emlib" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/inc" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/src" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/ff12b/src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"ff12b/doc/res/app2.d" -MT"ff12b/doc/res/app2.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ff12b/doc/res/app3.o: ../ff12b/doc/res/app3.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DEFM32WG842F256=1' '-DDEBUG=1' -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32WG/Include" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/emlib" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/inc" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/src" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/ff12b/src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"ff12b/doc/res/app3.d" -MT"ff12b/doc/res/app3.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ff12b/doc/res/app4.o: ../ff12b/doc/res/app4.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DEFM32WG842F256=1' '-DDEBUG=1' -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32WG/Include" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/emlib" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/inc" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/src" -I"/Users/aleboyer/SimplicityStudio/v4_workspace/Epsilometer/ff12b/src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"ff12b/doc/res/app4.d" -MT"ff12b/doc/res/app4.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


