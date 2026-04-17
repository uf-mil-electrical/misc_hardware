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
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(door-sense-v3-code C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(door-sense-v3-code main.c )

pico_set_program_name(door-sense-v3-code "door-sense-v3-code")
pico_set_program_version(door-sense-v3-code "1.0")


# Add all .c files here
target_sources(door-sense-v3-code PRIVATE
	communication/src/doorsense_uart.c
	communication/src/doorsense_i2c.c
	
	libraries/lcd/src/charlcd.c
	libraries/lcd/src/functions.c
	libraries/dfplayer/dfplayer.c
	libraries/tof/src/tof_calibration.c
	libraries/tof/src/tof_core.c
	libraries/tof/src/tof_i2c.c

	operation/operation.c

	peripherals/src/audio.c
    peripherals/src/lcd.c
	peripherals/src/leds.c
	peripherals/src/pot_adc.c
	peripherals/src/switches.c
	peripherals/src/tof.c
)


# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(door-sense-v3-code 0)
pico_enable_stdio_usb(door-sense-v3-code 1)

# Add the standard library to the build
target_link_libraries(door-sense-v3-code
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(door-sense-v3-code PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(door-sense-v3-code
        pico_stdlib
		pico_binary_info
		hardware_adc
		hardware_spi
		hardware_i2c
		hardware_pwm
		hardware_dma
		hardware_irq
		hardware_gpio
		hardware_clocks
		hardware_timer
		pico_time
		pico_rand
)

pico_add_extra_outputs(door-sense-v3-code)