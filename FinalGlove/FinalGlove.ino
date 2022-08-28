#include "CurieIMU.h"
int lastOrientation = - 1; // previous orientation (for comparison)
const int ThumbPin = A0;
const int PointerPin = A1;
const int MiddlePin = A2;
const int RingPin = A3;
const int PinkyPin = A4;
const int ElbowPin = A5;

int ThumbVal = 0;
int PointerVal = 0;
int MiddleVal = 0;
int RingVal = 0;
int PinkyVal = 0;
int ElbowVal = 0;

void setup() {
  Serial.begin(9600); // initialize Serial communication
  Serial1.begin(9600);
  // initialize device
  Serial.println("Initializing IMU device...");
  CurieIMU.begin();

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
}

void loop() {
int orientation = - 1;   // the board's orientation
  String orientationString; // string for printing description of orientation
  /*
    The orientations of the board:
    0: flat, processor facing up
    1: flat, processor facing down
    2: landscape, analog pins down
    3: landscape, analog pins up
    4: portrait, USB connector up
    5: portrait, USB connector down
  */
  // read accelerometer:
  int x = CurieIMU.readAccelerometer(X_AXIS);
  int y = CurieIMU.readAccelerometer(Y_AXIS);
  int z = CurieIMU.readAccelerometer(Z_AXIS);

  // calculate the absolute values, to determine the largest
  int absX = abs(x);
  int absY = abs(y);
  int absZ = abs(z);

  if ( (absZ > absX) && (absZ > absY)) {
    // base orientation on Z
    if (z > 0) {
      orientationString = "up";
      orientation = 0;  
    } else {
      orientationString = "down";
      orientation = 1;
    }
  } else if ( (absY > absX) && (absY > absZ)) {
    // base orientation on Y
    if (y > 0) {
      orientationString = "digital pins up";
      orientation = 2;
    } else {
      orientationString = "analog pins up";
      orientation = 3;
    }
  } else {
    // base orientation on X
    if (x < 0) {
      orientationString = "connector up";
      orientation = 4;
    } else {
      orientationString = "connector down";
      orientation = 5;
    }
  }

  ThumbVal = analogRead(ThumbPin);
  PointerVal = analogRead(PointerPin);
  MiddleVal = analogRead(MiddlePin);
  RingVal = analogRead(RingPin);
  PinkyVal = analogRead(PinkyPin);
  ElbowVal = analogRead(ElbowPin);

  ThumbVal = map(ThumbVal, 390, 640, 0, 180);
  PointerVal = map(PointerVal, 630, 1023, 0, 180);
  MiddleVal = map(MiddleVal, 390, 700, 0, 180);
  RingVal = map(RingVal, 530, 950, 0, 180);
  PinkyVal = map(PinkyVal, 930, 960, 0, 180);
  PinkyVal = PinkyVal / 2;
  //elbow not calculated
  ElbowVal = 0;

  Serial.print(orientation);
  Serial.print("/");
  Serial.print(ThumbVal);
  Serial.print("/");
  Serial.print(PointerVal);
  Serial.print("/");
  Serial.print(MiddleVal);
  Serial.print("/");
  Serial.print(RingVal);
  Serial.print("/");
  Serial.print(PinkyVal);
  Serial.print("/");
  Serial.print(ElbowVal);
  Serial.println("");

  Serial1.print(orientation);
  Serial1.print("/");
  Serial1.print(ThumbVal);
  Serial1.print("/");
  Serial1.print(PointerVal);
  Serial1.print("/");
  Serial1.print(MiddleVal);
  Serial1.print("/");
  Serial1.print(RingVal);
  Serial1.print("/");
  Serial1.print(PinkyVal);
  Serial1.print("/");
  Serial1.print(ElbowVal);
  Serial1.println("");
  
  // if the orientation has changed, print out a description:
    lastOrientation = orientation;
}





