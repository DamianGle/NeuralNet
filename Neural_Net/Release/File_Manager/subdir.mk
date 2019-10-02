################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../File_Manager/File_Manager.cpp 

OBJS += \
./File_Manager/File_Manager.o 

CPP_DEPS += \
./File_Manager/File_Manager.d 


# Each subdirectory must supply rules for building sources it contributes
File_Manager/%.o: ../File_Manager/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


