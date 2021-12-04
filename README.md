# RGB Etch-A-Sketch
Code for an Arduino-based simple Etch-A-Sketch-style tracing device using a 32x32 RGB LED matrix panel
(for Swarthmore College ENGR 015 Final Project)

Authors: Thomas Makin, Katelynn Swaim

### Components
- 32x32 RGB LED matrix panel
- Adafruit Metro M0
- Adafruit RGB Matrix Shield
- 2 rotary encoders (for x- and y-axis movement)
- Slide potentiometer (for color adjustment)
- 5x 10kΩ resistors

### Notes
- Final code is in the `etchASketch` sketch
- `debug_etchASketch` sketch disables one encoder to use pins 0 and 1 for UART debug serial

### Credits
Rotary Encoder Demo (source of `rotaryEncoder` sketch) © DroneBot Workshop 2019

RGBmatrixPanel library and `testshapes_32x32` sketch © Adafruit 2021
