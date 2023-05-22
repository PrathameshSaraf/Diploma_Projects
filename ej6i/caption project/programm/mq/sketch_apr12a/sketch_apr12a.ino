int pinRedLed = 11;
int pinGreenLed = 8;
int pinSensor = A5;
int THRESHOLD = 250;
void setup() {
pinMode(pinRedLed, OUTPUT);
pinMode(pinGreenLed, OUTPUT);
pinMode(pinSensor, INPUT);
Serial.begin(9600);
}
void loop() {
int analogValue = analogRead(pinSensor);
Serial.println("Val: " +analogValue);
digitalWrite(pinGreenLed, HIGH);
if (analogValue >= THRESHOLD) {
digitalWrite(pinGreenLed, LOW);
digitalWrite(pinRedLed, HIGH);
}
else {
digitalWrite(pinRedLed, LOW);
}
delay(5000);
}
