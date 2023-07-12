#define BLYNK_PRINT Serial
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN , DHTTYPE);
Adafruit_SSD1306 display = Adafruit_SSD1306(128 , 64 , &Wire);
int pinLED = 2;

char auth[] = "oPxujGi1_vXNVzN1l0Bt6rfvPQU3sVVe";
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

void setup() 
{
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  display.begin(SSD1306_SWITCHCAPVCC , 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE,BLACK);
  display.setCursor(0,0);
  display.print("Starting OS Blynk");
  display.display();
  pinMode(pinLED, OUTPUT);
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(". Wifi Is Connected! \r\n");
    digitalWrite(pinLED, HIGH);
    Serial.println("LED Wifi IS ON");
    }
}

void loop() 
{
  Blynk.run(); 
  float temp = dht.readTemperature();
  float humd = dht.readHumidity();
  Serial.begin(115200);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC , 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE,BLACK);
  display.setCursor(0,8);
  display.print("Temperature : "+ String(temp));
  display.setCursor(0,16);
  display.print("Humidity : "+ String(humd) + " %");
  display.display();
  Blynk.run();
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V0, humd);

}

