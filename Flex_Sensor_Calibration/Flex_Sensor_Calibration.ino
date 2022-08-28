const int FingerPin = A0;
int FingerVal = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(FingerPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  FingerVal = analogRead(FingerPin);
  FingerVal = map(FingerVal, 390 , 640 , 0 , 180);
  FingerVal -= 70;
  Serial.println(FingerVal);
  delay(1);  
}
