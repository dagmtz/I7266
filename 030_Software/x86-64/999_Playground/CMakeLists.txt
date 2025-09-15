cmake_minimum_required(VERSION 3.28)

# Project name
project("test" VERSION 0.1)

get_filename_component(CURRENT_DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Product filename
set(PRODUCT_NAME ${CURRENT_DIR_NAME})

# Directory for includes
set(INC_DIR inc)

# Directory for object files
set(OBJ_DIR obj)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OBJ_DIR})

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use AVR GCC toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER gcc)
set(CMAKE_C_COMPILER g++)

# Pass defines to compiler
add_definitions(
    -DDEBUG
)

# mmcu MUST be passed to bot the compiler and linker, this handle the linker
# set(CMAKE_EXE_LINKER_FLAGS )

add_compile_options(
#   -Os # optimize for size
    -Wall # enable warnings
    -Wno-main
    -Wundef
    -pedantic
    -g
)
file(GLOB SRC_FILES "src/*.c") # Load all files in src folder

# Include header files directories
include_directories(${INC_DIR})

# Create one target
add_executable(${PRODUCT_NAME} ${SRC_FILES})

# Rename the output to .elf as we will create multiple files
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ${PRODUCT_NAME})

# Clean extra files
file(GLOB OBJ_FILES "obj/*") # Load all files in obj folder
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${OBJ_FILES}")

