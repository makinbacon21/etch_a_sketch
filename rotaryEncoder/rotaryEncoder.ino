/*
  Rotary Encoder Demo
  rot-encode-demo.ino
  Demonstrates operation of Rotary Encoder
  Displays results on Serial Monitor
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// Rotary Encoder Inputs
//#define horizCLK 0
//#define horizDT 1
#define vertCLK 12
#define vertDT 13

// Slide Potentiometer
#define slide A5


int horizCounter = 0;
int currentHorizCLK;
int previousHorizCLK;

int vertCounter = 0;
int currentVertCLK;
int previousVertCLK;

int slider;

String horizDir = "";
String vertDir = "";

void setup() {
  // Set encoder pins as inputs
  //pinMode (horizCLK, INPUT);
  //pinMode (horizDT, INPUT);
  pinMode (vertCLK, INPUT);
  pinMode (vertDT, INPUT);

  // Set slider as input
  pinMode(slide, INPUT);

  // Setup Serial Monitor
  Serial.begin(115200);

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  //previousHorizCLK = digitalRead(horizCLK);
  previousVertCLK = digitalRead(vertCLK);
}

void loop() {
  // Read and print slider val
  slider = analogRead(slide);
  Serial.print("Slider: ");
  Serial.println(slider);
  
  // Read the current state of inputCLK
  //currentHorizCLK = digitalRead(horizCLK);
  currentVertCLK = digitalRead(vertCLK);

  // If the previous and the current state of the inputCLK are different then a pulse has occured
  //if (currentHorizCLK != previousHorizCLK) {

    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    //if (digitalRead(horizDT) != currentHorizCLK) {
      //horizCounter --;
      //horizDir = "CCW";

    //} else {
      // Encoder is rotating clockwise
      //horizCounter ++;
      //horizDir = "CW";

    //}
    //Serial.print("Horiz Direction: ");
    //Serial.print(horizDir);
    //Serial.print(" -- Value: ");
    //Serial.println(horizCounter);
  //}

  if (currentVertCLK != previousVertCLK) {

    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    if (digitalRead(vertDT) != currentVertCLK) {
      vertCounter --;
      vertDir = "CCW";

    } else {
      // Encoder is rotating clockwise
      vertCounter ++;
      vertDir = "CW";

    }
    Serial.print("Vert Direction: ");
    Serial.print(vertDir);
    Serial.print(" -- Value: ");
    Serial.println(vertCounter);
  }
  
  // Update previousStateCLK with the current state
  //previousHorizCLK = currentHorizCLK;
  previousVertCLK = currentVertCLK;
}
