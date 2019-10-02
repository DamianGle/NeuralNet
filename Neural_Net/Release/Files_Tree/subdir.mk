################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Files_Tree/Files_Tree.cpp 

OBJS += \
./Files_Tree/Files_Tree.o 

CPP_DEPS += \
./Files_Tree/Files_Tree.d 


# Each subdirectory must supply rules for building sources it contributes
Files_Tree/%.o: ../Files_Tree/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


