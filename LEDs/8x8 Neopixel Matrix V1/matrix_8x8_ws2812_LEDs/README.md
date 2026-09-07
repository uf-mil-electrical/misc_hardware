# Documentation for the 8x8 NeoPixel (ws2812) Programmable LED Matrix


Each NeoPixel can draw at max 60mA of current, so to account for 64 pixels, 

the maximum possible current draw of the NeoPixels would be 3.84 A. (64 \* 60mA = 3.84 A). 

In addition, Adafruit recommends a 300-500 Ohm resistor between the data output of the microcontroller and data input to the NeoPixels, and a 500-1000uF capacitor across the +5V and GND of the devices. 

Based on the max current draw, wire gauge needs to be 23 AWG \[2]. This means the typical sherlocks can't be used \[3]. Instead, this is the part that will be used: https://mm.digikey.com/Volume0/opasdata/d220001/medias/docus/377/1778638.pdf




### Sources 

\[1] “Adafruit NeoPixel Überguide,” Adafruit Learning System. https://learn.adafruit.com/adafruit-neopixel-uberguide/powering-neopixels
\[2] “American Wire Gauge Chart and AWG Electrical Current Load Limits table with ampacities, wire sizes, skin depth frequencies and wire breaking strength,” Powerstream.com, 2019. https://www.powerstream.com/Wire\_Size.htm
\[3] “2.0 W/B CONN. (Positive Lock) (2-20P, 6Kinds of color version) PS-35507-003” 2012. Accessed: May 15, 2026. \[Online]. Available: https://mm.digikey.com/Volume0/opasdata/d220001/medias/docus/2246/PS-35507-003.pdf

‌

