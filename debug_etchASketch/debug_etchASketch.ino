/*
  Rotary Encoder Demo
  rot-encode-demo.ino
  Demonstrates operation of Rotary Encoder
  Displays results on Serial Monitor
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

#include <RGBmatrixPanel.h>

// Rotary Encoder Inputs
#define horizCLK  0
#define horizDT   1

// LED Matrix Inputs
#define matrixCLK 8
#define matrixOE  9
#define matrixLAT 10
#define matrixA   A0
#define matrixB   A1
#define matrixC   A2
#define matrixD   A3

// Slide Potentiometer
#define slide     A4

RGBmatrixPanel matrix(matrixA, matrixB, matrixC, 
                      matrixD, matrixCLK, matrixLAT,
                      matrixOE, false);

int currentHorizCLK;
int previousHorizCLK;

long slider;

int x = 0;
int y = 63;
long hex;
uint16_t color;

void setup() {
  Serial.begin(9600);
  
  // Set encoder pins as inputs
  pinMode(horizCLK, INPUT);
  pinMode(horizDT, INPUT);

  // Set slider as input
  pinMode(slide, INPUT);

  // Init matrix
  matrix.begin();
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousHorizCLK = digitalRead(horizCLK);
}

void loop() {
  // Map slider to hex colors
  slider = analogRead(slide);
  Serial.print("Slider: " + String(slider));
  hex = slider * 0x50e8;
  Serial.print(" Hex: ");
  Serial.println(hex,16);
  int b = hex%0x100;
  int g = (hex/0x100)%0x100;
  int r = (hex/0x10000)%0x100;
  Serial.println("R: " + String(r) + " G: " +String(g) + " B: " +String(b));
  

  // Convert to RGB
  color = matrix.Color888(r, g, b);

  // Draw pixel at half x and y vals (encoders jump in 
  // multiples of 2)
  matrix.drawPixel(x/2, y/2, color);
  
  // Read the current state of inputCLK
  currentHorizCLK = digitalRead(horizCLK);

  // Check for horizontal encoder pulse
  if (currentHorizCLK != previousHorizCLK) {
    // If the DT != CLK then go left
    if (digitalRead(horizDT) != currentHorizCLK) {
      x--;
    } else {
      // Go right
      x++;
    }

    // Handle rollover
    if(x > 63) {
      x = 0;
    }
    else if(x < 0) {
      x = 63;
    }
  }
  
  // Update states
  previousHorizCLK = currentHorizCLK;
  delay(10);
}
