# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/usr/share/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(mico C CXX ASM)

# Generate compile_commands.json for lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(mico mico.cpp )

pico_set_program_name(mico "mico")
pico_set_program_version(mico "0.1")

pico_enable_stdio_uart(mico 0)
pico_enable_stdio_usb(mico 1)

# Add the standard library to the build
target_link_libraries(mico pico_stdlib)

add_subdirectory(libs)

# pio
# pico_generate_pio_header(mico ${CMAKE_CURRENT_LIST_DIR}/quadrature_encoder.pio)

target_link_libraries(mico encoder-pio)

# Add any user requested libraries
target_link_libraries(mico
		pico_multicore
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        )

pico_add_extra_outputs(mico)
