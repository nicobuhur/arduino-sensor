#include <DHT.h>
#include <SD.h>

#define DHTPIN 2      // Assuming you connect the DHT sensor to digital pin 2
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

const int chipSelect = 10; // Chip select pin for SD card module
const int printInterval = 2000; // Print data every 2 seconds (in milliseconds)
const int recordInterval = 300000; // Record data every 5 minutes (in milliseconds)

const int blueLED = 3;  // Blue LED connected to digital pin 3
const int greenLED = 4; // Green LED connected to digital pin 4
const int redLED = 5;   // Red LED connected to digital pin 5

const int gasSensorPin = A0; // Gas sensor connected to analog pin A0
const int buzzerPin = 6;     // Buzzer connected to digital pin 6
const int gasThreshold = 200;

unsigned long previousPrintMillis = 0;
unsigned long previousRecordMillis = 0;
bool ledTestDone = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");

  dht.begin();

  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Run LED test at the beginning
  ledTestDone = false;
  runLedTest();

  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization done.");
}

void runLedTest() {
  // Test LEDs by blinking 10 times in 1 second
  for (int i = 0; i < 10; i++) {
    digitalWrite(blueLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer during the LED test
    delay(50);
    digitalWrite(blueLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
    delay(50);
  }

  delay(3000); // 3-second delay after LED test
  ledTestDone = true;
}

void controlLEDs(float temperature) {
  // Control LEDs based on temperature
  if (temperature < 20) {
    // Only blue LED on
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, HIGH);
  } else if (temperature >= 20 && temperature < 22) {
    // Blue and green LEDs on
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, HIGH);
    digitalWrite(greenLED, HIGH);
  } else if (temperature >= 22 && temperature < 24) {
    // Green LEDs on
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(greenLED, HIGH);
  } else if (temperature >= 24 && temperature < 26) {
    // Green and red LEDs on
    digitalWrite(blueLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, HIGH);
  } else {
    // Only red LED on
    digitalWrite(blueLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(10);
    digitalWrite(buzzerPin, LOW);
  }
}

void blinkRedLED() {
  // Blink the red LED three times
  for (int i = 0; i < 3; i++) {
    digitalWrite(redLED, HIGH);
    delay(200);
    digitalWrite(redLED, LOW);
    delay(200);
  }
}

void loop() {
  unsigned long currentMillis = millis();

  // Run LED test before reading temperature
  if (!ledTestDone) {
    runLedTest();
    previousPrintMillis = currentMillis;
    previousRecordMillis = currentMillis;
    return;
  }

  float h, t; // Declare h and t here

  // Check if 2 seconds have passed for printing
  if (currentMillis - previousPrintMillis >= printInterval) {
    previousPrintMillis = currentMillis;

    h = dht.readHumidity();
    t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("Error while reading the DHT sensor");
      return;
    }

    Serial.print("Temperature = ");
    Serial.print(t);
    Serial.println("°C");

    Serial.print("Humidity = ");
    Serial.print(h);
    Serial.println("%");

    // Control LEDs based on temperature
    controlLEDs(t);
  }

  // Check if 5 minutes have passed for SD card recording
  if (currentMillis - previousRecordMillis >= recordInterval) {
    previousRecordMillis = currentMillis;

    // Open the file
    File myFile = SD.open("data.txt", FILE_WRITE);

    // If the file opened okay, write to it
    if (myFile) {
      myFile.print("Temperature = ");
      myFile.print(t);
      myFile.println("°C");

      myFile.print("Humidity = ");
      myFile.print(h);
      myFile.println("%");

      myFile.close();
      Serial.println("Data written to SD card.");
    } else {
      // If the file didn't open, print an error
      Serial.println("Error opening data.txt");
    }
  }

  int gasSensorValue = analogRead(gasSensorPin);

  // Print gas sensor value to the serial monitor
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasSensorValue);

  if (gasSensorValue > gasThreshold) {
    // Gas detected, activate the buzzer 10 times
    for (int i = 0; i < 5; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(50); // 0.5 seconds delay
      digitalWrite(buzzerPin, LOW);
      delay(50); // 0.5 seconds delay
    }
  }

  // Delay before the next iteration
  delay(1000);
}
