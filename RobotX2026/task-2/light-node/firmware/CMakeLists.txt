cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(light-node-firmware C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default is main.c
add_executable(light-node-firmware
   src/main.cpp
)

add_subdirectory(lib/pico_neopixel)

# Link against pico_stdlib
target_link_libraries(light-node-firmware 
    pico_stdlib 
    hardware_i2c 
    hardware_uart
    pico_neopixel)

# Enable USB or UART output
pico_enable_stdio_usb(light-node-firmware 1)
pico_enable_stdio_uart(light-node-firmware 0)
target_link_libraries(light-node-firmware pico_stdlib)


# Create map/bin/hex/uf2 file in output
pico_add_extra_outputs(light-node-firmware)


target_link_options(light-node-firmware PRIVATE
    $<$<LINK_LANGUAGE:CXX>:-nostdlib++>
)

target_compile_options(light-node-firmware PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
)
