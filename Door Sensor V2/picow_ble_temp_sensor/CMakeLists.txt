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
project(picow_ble_temp_sensor C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(picow_ble_temp_sensor
    server.c
    )

pico_set_program_name(picow_ble_temp_sensor "picow_ble_temp_sensor")
pico_set_program_version(picow_ble_temp_sensor "0.1")

# Add other program files to build
target_sources(Door-Sense-Code-V2 PRIVATE
    peripherals/src/doorsense_gpio.c
    peripherals/src/doorsense_i2c.c
    peripherals/src/doorsense_spi.c
    peripherals/src/doorsense_uart.c
	
	tof_lib/src/tof_core.c
	tof_lib/src/tof_i2c.c
	tof_lib/src/tof_calibration.c

	operation/src/door_state.c
)


# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Door-Sense-Code-V2 0)
pico_enable_stdio_usb(Door-Sense-Code-V2 1)


# Add libraries
target_link_libraries(picow_ble_temp_sensor
    pico_stdlib
    pico_btstack_ble
    pico_btstack_cyw43
    pico_cyw43_arch_none
    hardware_adc
    )

# Include btstack directories and config
target_include_directories(picow_ble_temp_sensor PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/.. # For our common btstack config
    )

# Generate the GATT header file from the temp_sensor.gatt file
pico_btstack_make_gatt_header(picow_ble_temp_sensor PRIVATE "${CMAKE_CURRENT_LIST_DIR}/temp_sensor.gatt")

pico_add_extra_outputs(picow_ble_temp_sensor)
