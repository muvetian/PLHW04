################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/blackjack.cpp \
../src/card.cpp \
../src/crazy8.cpp \
../src/mjmplayer.cpp \
../src/play.cpp \
../src/player.cpp \
../src/shedgame.cpp \
../src/switch.cpp 

OBJS += \
./src/blackjack.o \
./src/card.o \
./src/crazy8.o \
./src/mjmplayer.o \
./src/play.o \
./src/player.o \
./src/shedgame.o \
./src/switch.o 

CPP_DEPS += \
./src/blackjack.d \
./src/card.d \
./src/crazy8.d \
./src/mjmplayer.d \
./src/play.d \
./src/player.d \
./src/shedgame.d \
./src/switch.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


