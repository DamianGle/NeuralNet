################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PNG/font_png.cpp \
../PNG/graph_png.cpp \
../PNG/lodepng.cpp \
../PNG/png.cpp 

OBJS += \
./PNG/font_png.o \
./PNG/graph_png.o \
./PNG/lodepng.o \
./PNG/png.o 

CPP_DEPS += \
./PNG/font_png.d \
./PNG/graph_png.d \
./PNG/lodepng.d \
./PNG/png.d 


# Each subdirectory must supply rules for building sources it contributes
PNG/%.o: ../PNG/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


