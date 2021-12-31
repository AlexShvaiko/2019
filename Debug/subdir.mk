################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../asembler.c \
../codef.c \
../dc.c \
../read.c \
../readb.c \
../symtab.c 

O_SRCS += \
../asembler.o \
../dc.o \
../myprog.o \
../read.o \
../readb.o \
../symtab.o 

OBJS += \
./asembler.o \
./codef.o \
./dc.o \
./read.o \
./readb.o \
./symtab.o 

C_DEPS += \
./asembler.d \
./codef.d \
./dc.d \
./read.d \
./readb.d \
./symtab.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


