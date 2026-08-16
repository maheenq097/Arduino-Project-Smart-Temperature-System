#include <DHT.h>
#include <Stepper.h>

#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Stepper setup
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); // IN1, IN3, IN2, IN4 order

// LED pins
const int redLED = 2;
const int yellowLED = 3;
const int blueLED = 4;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  myStepper.setSpeed(10);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float tempC = dht.readTemperature();

  if (isnan(tempC)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(1000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" °C");

  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(blueLED, LOW);

  if (tempC > 35) {
    digitalWrite(redLED, HIGH);
    Serial.println("Stepping now...");
    myStepper.step(stepsPerRevolution / 8);
  } else if (tempC >= 25 && tempC <= 35) {
    digitalWrite(yellowLED, HIGH);
  } else {
    digitalWrite(blueLED, HIGH);
  }

  delay(2000); // DHT11 needs at least 1s between reads, 2s is safer
}