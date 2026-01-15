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
set(sdkVersion 2.2.0)
set(toolchainVersion RISCV_ZCB_RPI_2_2_0_3)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
project(door-sense-v2-code C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(door-sense-v2-code
    main.c
    )

pico_set_program_name(door-sense-v2-code "door-sense-v2-code")
pico_set_program_version(door-sense-v2-code "0.1")

# Add other .c files in project
target_sources(door-sense-v2-code PRIVATE
	peripherals/src/doorsense_ble.c
    peripherals/src/doorsense_gpio.c
    peripherals/src/doorsense_i2c.c
    peripherals/src/doorsense_spi.c
    peripherals/src/doorsense_uart.c
	
	tof_lib/src/tof_core.c
	tof_lib/src/tof_i2c.c
	tof_lib/src/tof_calibration.c

	operation/src/door_state.c
)

# Enable/disable output over UART/USB
pico_enable_stdio_uart(door-sense-v2-code 0)
pico_enable_stdio_usb(door-sense-v2-code 1)

# Add necessary libraries
target_link_libraries(door-sense-v2-code
    pico_stdlib
    pico_btstack_ble
    pico_btstack_cyw43
    pico_cyw43_arch_none
    hardware_adc
	hardware_i2c
	hardware_spi
	hardware_uart
    )

# BLE-related directories
target_include_directories(door-sense-v2-code PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/.. # For our common btstack config
    )

pico_add_extra_outputs(door-sense-v2-code)