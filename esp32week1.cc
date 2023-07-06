#define BLYNK_PRINT Serial
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "jcv43XhcfyIXGPPBYTSnUdR1i8DzFuC9";
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

int pinRED = 15;
int pinYEL = 4;
int pinGEN = 5;
int pinLED = 2;

unsigned long previousMillis = 0;
unsigned long interval = 120;

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("Disconnected from WiFi access point");
  Serial.print("WiFi lost connection.");
  Serial.println("Trying to Reconnect");
  WiFi.begin(ssid, pass);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start Blynk Your Console");
  Blynk.begin(auth, ssid, pass);
  pinMode(pinRED, OUTPUT);
  pinMode(pinYEL, OUTPUT);
  pinMode(pinGEN, OUTPUT);
  pinMode(pinLED, OUTPUT);
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(". Wifi Is Connected! \r\n");
    digitalWrite(pinLED, HIGH);
    Serial.println("LED Wifi IS ON");
    }
  }


void loop() {
  Blynk.run();
  unsigned long currentMillis = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi... \r\n");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
    }

}

//RED
BLYNK_WRITE(V1){
  int ledState = param.asInt();
  if(ledState == 1){
    digitalWrite(pinRED, HIGH);
    digitalWrite(pinYEL, LOW);
    digitalWrite(pinGEN, LOW);
    Serial.println("LED RED IS ON");
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 0);
  }else if(ledState == 0){
    digitalWrite(pinRED, LOW);
    Serial.println("LED RED IS OFF");
    }
  }

//YELLOW
BLYNK_WRITE(V2){
  int ledState = param.asInt();
  if(ledState == 1){
    digitalWrite(pinYEL, HIGH);
    digitalWrite(pinRED, LOW);
    digitalWrite(pinGEN, LOW);
    Serial.println("LED YELLOW IS ON");
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V3, 0);
  }else if(ledState == 0){
    digitalWrite(pinYEL, LOW);
    Serial.println("LED YELLOW IS OFF");
    }
  }

//GREEN
BLYNK_WRITE(V3){
  int ledState = param.asInt();
  if(ledState == 1){
    digitalWrite(pinGEN, HIGH);
    digitalWrite(pinYEL, LOW);
    digitalWrite(pinRED, LOW);
    Serial.println("LED BLUE IS ON");
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 0);
  }else if(ledState == 0){
    digitalWrite(pinGEN, LOW);
    Serial.println("LED BLUE IS OFF");
    }
  }
