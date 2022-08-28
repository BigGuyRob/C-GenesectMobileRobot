const int FingerPin = A#;
int FingerVal = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(FingerPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  FingerVal = analogRead(FingerPin);
  FingerVal = map(FingerVal, MIN_VAL, MAX_VAL , 0 , 180);
  Serial.println(FingerVal);
}
