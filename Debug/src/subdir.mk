################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Psychedelic\ video.cpp 

OBJS += \
./src/Psychedelic\ video.o 

CPP_DEPS += \
./src/Psychedelic\ video.d 


# Each subdirectory must supply rules for building sources it contributes
src/Psychedelic\ video.o: ../src/Psychedelic\ video.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I-I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Psychedelic video.d" -MT"src/Psychedelic\ video.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


