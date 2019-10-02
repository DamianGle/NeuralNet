################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../GraphConv_2D/GraphConv_2D.cpp 

OBJS += \
./GraphConv_2D/GraphConv_2D.o 

CPP_DEPS += \
./GraphConv_2D/GraphConv_2D.d 


# Each subdirectory must supply rules for building sources it contributes
GraphConv_2D/%.o: ../GraphConv_2D/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


