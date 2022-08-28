#include <Servo.h>

Servo myservo;  // create servo object to control a servo
                // twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup()
{
  Serial1.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
  if(Serial1.read() == 3){
    myservo.write(pos + 10);
  }
  if(Serial1.read() == 2){
    myservo.write(pos - 10);
  }
}
