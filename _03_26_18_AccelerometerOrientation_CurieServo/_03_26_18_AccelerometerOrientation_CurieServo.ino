int Thumb = A0;
int Point = A1;
int Mid = A2;
#include "CurieIMU.h"
int lastOrientation = - 1; // previous orientation (for comparison)
void setup() {
  Serial.begin(9600); // initialize Serial communication
  Serial1.begin(9600);
  // initialize device
  //Serial.println("Initializing IMU device...");
  CurieIMU.begin();

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
  pinMode(Thumb, INPUT);
  pinMode(Point, INPUT);
  pinMode(Mid, INPUT);
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

  // if the orientation has changed, print out a description:
    Serial.println(orientation);
    Serial1.println(orientation);
    //Serial1.write(analogRead(Thumb));
    //Serial1.write(analogRead(Point));
    //Serial1.write(analogRead(Mid));
    lastOrientation = orientation;
    delay(1);
}




