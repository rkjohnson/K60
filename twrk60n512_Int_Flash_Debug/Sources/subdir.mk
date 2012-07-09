################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/accel_task.c" \
"../Sources/adc16.c" \
"../Sources/adc_task.c" \
"../Sources/main_task.c" \
"../Sources/rtcs_init.c" \
"../Sources/tower_io.c" \

C_SRCS += \
../Sources/accel_task.c \
../Sources/adc16.c \
../Sources/adc_task.c \
../Sources/main_task.c \
../Sources/rtcs_init.c \
../Sources/tower_io.c \

OBJS += \
./Sources/accel_task.obj \
./Sources/adc16.obj \
./Sources/adc_task.obj \
./Sources/main_task.obj \
./Sources/rtcs_init.obj \
./Sources/tower_io.obj \

OBJS_QUOTED += \
"./Sources/accel_task.obj" \
"./Sources/adc16.obj" \
"./Sources/adc_task.obj" \
"./Sources/main_task.obj" \
"./Sources/rtcs_init.obj" \
"./Sources/tower_io.obj" \

C_DEPS += \
./Sources/accel_task.d \
./Sources/adc16.d \
./Sources/adc_task.d \
./Sources/main_task.d \
./Sources/rtcs_init.d \
./Sources/tower_io.d \

C_DEPS_QUOTED += \
"./Sources/accel_task.d" \
"./Sources/adc16.d" \
"./Sources/adc_task.d" \
"./Sources/main_task.d" \
"./Sources/rtcs_init.d" \
"./Sources/tower_io.d" \

OBJS_OS_FORMAT += \
./Sources/accel_task.obj \
./Sources/adc16.obj \
./Sources/adc_task.obj \
./Sources/main_task.obj \
./Sources/rtcs_init.obj \
./Sources/tower_io.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/accel_task.obj: ../Sources/accel_task.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/accel_task.args" -o "Sources/accel_task.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/adc16.obj: ../Sources/adc16.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/adc16.args" -o "Sources/adc16.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/adc16.d: ../Sources/adc16.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/adc_task.obj: ../Sources/adc_task.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/adc_task.args" -o "Sources/adc_task.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_task.obj: ../Sources/main_task.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/main_task.args" -o "Sources/main_task.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/rtcs_init.obj: ../Sources/rtcs_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/rtcs_init.args" -o "Sources/rtcs_init.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/tower_io.obj: ../Sources/tower_io.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/tower_io.args" -o "Sources/tower_io.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


