# I target a recent cmake, it shouldn't be a problem on a dev machine
cmake_minimum_required(VERSION 3.28)

# Project name
project("Default" VERSION 0.1)

# Product filename
set(PRODUCT_NAME result)

# Directory for includes
set(INC_DIR inc)

# Directory for object files
set(OBJ_DIR obj)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OBJ_DIR})

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## AVR Chip Configuration
# 8Mhz, this should match the crystal on your board,
# I use 8Mhz and 3.3V for the lowest power consumption
set(F_CPU 16000000UL)
# CPU, you can find the list here:
# https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html
set(MCU atmega328p)
# DS3231 Baudrate for UART, read avr include/util/setbaud.h for usage
set(BAUD 9600)
# The programmer to use, read avrdude manual for list
set(PROG_TYPE usbasp)

# AVR Fuses, must be in concordance with your hardware and F_CPU
# http://eleccelerator.com/fusecalc/fusecalc.php?chip=atmega328p
# set(E_FUSE 0xfd)
# set(H_FUSE 0xda)
# set(L_FUSE 0xfd)
# set(LOCK_BIT 0xff)

# Use AVR GCC toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)

# Pass defines to compiler
add_definitions(
    -DF_CPU=${F_CPU}
    # -DBAUD=${BAUD}
    # -DUSART 
    # -DUSART_DEBUG
)

# mmcu MUST be passed to bot the compiler and linker, this handle the linker
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})

add_compile_options(
    -mmcu=${MCU} # MCU
    -std=gnu99 # C99 standard
    -Os # optimize for size
    -Wall # enable warnings
    -Wno-main
    -Wundef
    -pedantic
    -Wstrict-prototypes
    # -Werror
    # -Wfatal-errors
    # -Wno-array-bounds
    # -Wl,--relax,--gc-sections
    -g
    # -gdwarf-2
    -funsigned-char # a few optimizations
    -funsigned-bitfields
    -fpack-struct
    -fshort-enums
    -ffunction-sections
    -fdata-sections
    # -fno-split-wide-types
    # -fno-tree-scev-cprop
)
file(GLOB SRC_FILES "src/*.c") # Load all files in src folder

# Include header files directories
include_directories(${INC_DIR})

# Create one target
add_executable(${PRODUCT_NAME} ${SRC_FILES})

# Rename the output to .elf as we will create multiple files
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ${PRODUCT_NAME}.elf)

# Strip binary for upload
add_custom_target(strip ALL avr-strip ${OBJ_DIR}/${PRODUCT_NAME}.elf DEPENDS ${OBJ_DIR}/${PRODUCT_NAME})

# Transform binary into hex file, we ignore the eeprom segments in the step
# add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${OBJ_DIR}/${PRODUCT_NAME}.elf ${OBJ_DIR}/${PRODUCT_NAME}.hex DEPENDS strip)
add_custom_target(hex ALL avr-objcopy -O ihex ${OBJ_DIR}/${PRODUCT_NAME}.elf ${OBJ_DIR}/${PRODUCT_NAME}.hex DEPENDS strip)
# Transform binary into hex file, this is the eeprom part (empty if you don't
# use eeprom static variables)
# add_custom_target(eeprom avr-objcopy -j .eeprom  --set-section-flags=.eeprom="alloc,load"  --change-section-lma .eeprom=0 -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.eep DEPENDS strip)

# Upload the firmware with avrdude
# add_custom_target(upload sudo avrdude  -c ${PROG_TYPE} -p ${MCU} -U flash:w:${OBJ_DIR}/${PRODUCT_NAME}.hex DEPENDS hex)
add_custom_target(upload avrdude  -c ${PROG_TYPE} -p ${MCU} -U flash:w:${OBJ_DIR}/${PRODUCT_NAME}.hex DEPENDS hex)

# Upload the eeprom with avrdude
# add_custom_target(upload_eeprom avrdude -c ${PROG_TYPE} -p ${MCU}  -U eeprom:w:${PRODUCT_NAME}.eep DEPENDS eeprom)

# Burn fuses
# add_custom_target(fuses avrdude -c ${PROG_TYPE} -p ${MCU}  -U lfuse:w:${L_FUSE}:m -U hfuse:w:${H_FUSE}:m -U efuse:w:${E_FUSE}:m -U lock:w:${LOCK_BIT}:m )

# Start serial communication with screen 
add_custom_target(serial0 sudo screen /dev/ttyUSB0 ${BAUD})
add_custom_target(serial1 sudo screen /dev/ttyUSB1 ${BAUD})

# Clean extra files
file(GLOB OBJ_FILES "obj/*") # Load all files in obj folder
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${OBJ_FILES}")

