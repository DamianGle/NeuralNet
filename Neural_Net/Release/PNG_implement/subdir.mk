################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PNG_implement/font_png.cpp \
../PNG_implement/graph_png.cpp \
../PNG_implement/lodepng.cpp \
../PNG_implement/png.cpp 

OBJS += \
./PNG_implement/font_png.o \
./PNG_implement/graph_png.o \
./PNG_implement/lodepng.o \
./PNG_implement/png.o 

CPP_DEPS += \
./PNG_implement/font_png.d \
./PNG_implement/graph_png.d \
./PNG_implement/lodepng.d \
./PNG_implement/png.d 


# Each subdirectory must supply rules for building sources it contributes
PNG_implement/%.o: ../PNG_implement/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


