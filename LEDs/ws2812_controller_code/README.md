# Expanded NeoPixel Library

### Purpose of library:
- pico sdk example is fine for processes that are not timing critical, but using the DMA to control the data sent is a better method if the cpu needs to be used for another process at the same time
- easy integration into projects where pico is only controlling the neopixels and is also controlling other things

### Structure of Project:

```
.ws2812_controller_code
├── .vscode/
├── build/
├── include/
│   └── ws2812_controller_functions.h
├── src/
│   ├── LED_output.pio
│   ├── ws2812_controller_code.c
│   └── ws2812_controller_functions.c
├── .gitignore
├── CMakeLists.txt
├── pico_sdk_import.cmake
└── README.md
```

**LED_output.pio :**  .pio program for controlling the output
**ws2812_controller_functions.c :** c file with functions for code
**ws2812_controller_functions.h :** header file for funcitons
**ws2812_controller_code.c :** example uses of each function
**CMakeLists.txt :** example CMake file. Important note: must include directory where .pio file is located in target_include_directories (because the file makes the associated header file)

<br>

# Function Documentation



<br>

``` c 
bool config_neopixel_gpio_pins(int gpio_pin1, int gpio_pin2)
```
Configures the GPIO pins to be used with the neopixels. 

Parameters:
> `int gpio_pin1`      Number of the first GPIO pin used by the .pio program
> `int gpio_pin2`       Number of the second GPIO pinused by the .pio program

Returns:
> Returns true if the configuration  of the GPIO pins was successful.

<br>




---

<br>

``` c 
bool set_color_solid_mode()
```
description

Parameters:
> ``      
> ``    

Returns:
> Returns true if 


- set color output, solid color
    - red, green, blue values of color 0 -> 255
    - potential for future expansion with bitmasks and the like
<br>






--- 

<br>

``` c 
bool set_color_animated_mode()
```
description

Parameters:
> ``      
> ``    

Returns:
> Returns true if 


- start color output, animation mode
    - change point to start of associated LUT 
    - potential for future expansion with bitmasks and the like





---

<br>

``` c 
bool start_output_solid_mode()
```
Starts output of a **solid color** to the neopixel pins. Claims and starts relevant pio state machines and 2 DMA channels. Must be used after _____.

Parameters:
> ``      description
> ``      description

Returns:
> Returns true if 

- init. neopixel output led strip / solid mode

  - feed in # pixels, pio to use, any other DMA settings im blanking on rn 

  - panics and error if any value fed in is out of range sm is being used by something else

<br>






---

<br>

``` c 
bool start_output_animated_mode()
```
description

Parameters:
> ``      
> ``       

Returns:
> Returns true if 

- init. neopixel output animation mode

  - feed in # pixels, pio to use, number of frames in animation, any other DMA settings im blanking on rn 

  - panics and error if any value fed in is out of range sm is being used by something else

<br>






---

<br>

``` c 
bool stop_color_output()
```
description

Parameters:
> ``      
> ``    

Returns:
> Returns true if 

- stop color output, for both
  - num pixels, other DMA settings to edit transfer information
  - still technically outputting, just zero constantly
  - changes dma channel to transfer 1 for num pixels then wait
  
<br>