################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BPN_NeuralNetwork/NeuralNetwork.cpp \
../BPN_NeuralNetwork/NeuralNetworkTrainer.cpp \
../BPN_NeuralNetwork/TrainingDataReader.cpp 

OBJS += \
./BPN_NeuralNetwork/NeuralNetwork.o \
./BPN_NeuralNetwork/NeuralNetworkTrainer.o \
./BPN_NeuralNetwork/TrainingDataReader.o 

CPP_DEPS += \
./BPN_NeuralNetwork/NeuralNetwork.d \
./BPN_NeuralNetwork/NeuralNetworkTrainer.d \
./BPN_NeuralNetwork/TrainingDataReader.d 


# Each subdirectory must supply rules for building sources it contributes
BPN_NeuralNetwork/%.o: ../BPN_NeuralNetwork/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


