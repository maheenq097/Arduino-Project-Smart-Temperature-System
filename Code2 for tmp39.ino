const int tempPin = A0;

const int redLED = 8;
const int yellowLED = 9;
const int blueLED = 10;
const int fanPin = 7;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int rawValue = analogRead(tempPin);
  float voltage = rawValue * (5.0 / 1023.0);
  float tempC = (voltage - 0.5) * 100.0;  // TMP36 formula

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" °C");

  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(fanPin, LOW);

  if (tempC > 35) {
    digitalWrite(redLED, HIGH);
    digitalWrite(fanPin, HIGH);
  } else if (tempC >= 25 && tempC <= 35) {
    digitalWrite(yellowLED, HIGH);
  } else {
    digitalWrite(blueLED, HIGH);
  }

  delay(1000);
}
