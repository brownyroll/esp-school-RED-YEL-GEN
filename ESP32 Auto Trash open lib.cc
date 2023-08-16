#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Servo servo;
const int trigPin = 5; // Connect Ultrasonic sensor Trig pin to D5
const int echoPin = 18; // Connect Ultrasonic sensor Echo pin to D18
const int servoPin = 13; // Connect Servo signal pin to D13

void setup() {
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  
  servo.attach(servoPin);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Smart Trash Can");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  long duration, distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Calculate distance in cm
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Distance: ");
  display.print(distance);
  display.print(" cm");
  
  if (distance < 10) {
    servo.write(90); // Close the lid
    display.setCursor(0, 20);
    display.println("Trash is Unknown Person");
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);

    Serial.print("Close the lid Trash \r\n");
  } else {
    servo.write(0); // Open the lid
    display.setCursor(0, 20);
    display.println("Trash is See Person ");
    digitalWrite(4, HIGH);
    digitalWrite(2, LOW);
    Serial.print("Open the lid Trash \r\n");
  }
  
  display.display();
  
  delay(1000);

}
