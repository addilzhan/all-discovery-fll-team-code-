#include <GyverNTC.h>
#define TdsSensorPin A0
#define VREF 5.0
#define ADC_RESOLUTION 1024.0  
GyverNTC therm(1, 10000, 3950);

float tdsFactor = 0.5;
float temperature = 25;
const int trigPin = 9;
const int echoPin = 10;

unsigned long previousMillis = 0;
const long interval = 10000; // 10-second interval

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

float getTDSValue() {
  int sensorValue = analogRead(TdsSensorPin);
  float voltage = sensorValue * (VREF / ADC_RESOLUTION);
  float tdsValue = (voltage / VREF) * 1000;
  float ppmValue = tdsValue / (1.0 + 0.02 * (temperature - 25));
  return ppmValue;
}

float getTemperature() {
  return therm.getTempAverage();
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if 10 seconds have passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Get sensor data
    float tdsValue = getTDSValue();
    float currentTemperature = getTemperature();
    int distance = getDistance();

    // Create an array to hold the data
    float data[3];
    data[0] = tdsValue;
    data[1] = currentTemperature;
    data[2] = distance;

    // Print the array elements in one line
    Serial.print(data[0]);
    Serial.print(",");
    Serial.print(data[1]);
    Serial.print(",");
    Serial.print(data[2]);
    Serial.println(); // End of line
  }
}
