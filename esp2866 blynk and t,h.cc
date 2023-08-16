#define BLYNK_PRINT Serial
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN D4
DHT dht(DHTPIN, DHTTYPE); 
float t;
float h;

char auth[] = "oPxujGi1_vXNVzN1l0Bt6rfvPQU3sVVe";
char ssid[] = "C:/Brownyrollz/index.ts";
char pass[] = "00000000";
void setup()
{
    dht.begin();
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    Serial.print("Starting OS Blynk");
    
}

void loop()
{
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  Serial.println("Humidity and temperature\n\n");
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t); 
  Serial.print("\r\n");
  Blynk.run(); 
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}
