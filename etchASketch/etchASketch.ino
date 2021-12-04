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
#define vertCLK   12
#define vertDT    13

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

int currentVertCLK;
int previousVertCLK;

int slider;

int x = 0;
int y = 63;
int hex;
int prevHex;
int firstHex;

uint16_t color;

void setup() {
  // Set encoder pins as inputs
  pinMode(horizCLK, INPUT);
  pinMode(horizDT, INPUT);
  pinMode(vertCLK, INPUT);
  pinMode(vertDT, INPUT);

  // Set slider as input
  pinMode(slide, INPUT);

  // Init matrix
  matrix.begin();
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousHorizCLK = digitalRead(horizCLK);
  previousVertCLK = digitalRead(vertCLK);

  slider = analogRead(slide);
  hex = slider * 0x50e8;
  prevHex = hex;
  firstHex = hex;
}

void loop() {
  // Map slider to hex colors
  slider = analogRead(slide);
  firstHex = prevHex;
  prevHex = hex;
  hex = slider * 0x50e8;

  int avg = (hex + prevHex + firstHex)/3;
  
  int b = avg%0x100;
  int g = (avg/0x100)%0x100;
  int r = (avg/0x10000)%0x100;

  // Convert to RGB
  color = matrix.Color888(r, g, b);

  // Draw pixel at half x and y vals (encoders jump in 
  // multiples of 2)
  matrix.drawPixel(x/2, y/2, color);

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

  // Check for vertical encoder pulse
  if (currentVertCLK != previousVertCLK) {
    // If the DT != CLK then go down
    if (digitalRead(vertDT) != currentVertCLK) {
      y--;
    } else {
      // Go up
      y++;
    }

    // Handle rollover
    if(y > 63) {
      y = 0;
    }
    else if(y < 0) {
      y = 63;
    }
  }
  
  // Update states
  previousHorizCLK = currentHorizCLK;
  previousVertCLK = currentVertCLK;
}
