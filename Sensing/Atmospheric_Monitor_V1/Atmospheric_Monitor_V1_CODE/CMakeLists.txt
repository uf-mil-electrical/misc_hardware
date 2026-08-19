# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.3.0)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Atmospheric_Monitor_V1_CODE C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(Atmospheric_Monitor_V1_CODE main.c )

pico_set_program_name(Atmospheric_Monitor_V1_CODE "Atmospheric_Monitor_V1_CODE")
pico_set_program_version(Atmospheric_Monitor_V1_CODE "0.1")

# Add all .c files here
target_sources(Atmospheric_Monitor_V1_CODE PRIVATE
    communication/src/pico_spi.c

	peripherals/src/leds.c
    peripherals/src/thermistors.c
)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Atmospheric_Monitor_V1_CODE 0)
pico_enable_stdio_usb(Atmospheric_Monitor_V1_CODE 1)

# Add libraries to the build
target_link_libraries(Atmospheric_Monitor_V1_CODE
        pico_stdlib
        hardware_adc
        hardware_gpio
        hardware_pwm
        hardware_spi
        )

# Add the standard include files to the build
target_include_directories(Atmospheric_Monitor_V1_CODE PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(Atmospheric_Monitor_V1_CODE)
