
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLTOSP_-du"
#define BLYNK_DEVICE_NAME "PAVAN"
#define BLYNK_AUTH_TOKEN "RL9toZCzf0It1NKt7cXHT4nt7fUiyK50"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG


// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI
int ledpin = 13;
int pump1 = 12;
int pump2 = 4;
int pump3 = 14;
int pump4 = 1;
#include "BlynkEdgent.h"
SimpleTimer timer;
 
 
 
#define ONE_WIRE_BUS 2 // DS18B20 on arduino pin2 corresponds to D4 on physical board "D4 pin on the ndoemcu Module"
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float temp;
float Fahrenheit=0;

BLYNK_WRITE(V0){
  int pinvalue = param.asInt();
  digitalWrite(ledpin,pinvalue);
  }
BLYNK_WRITE(V1){
  int pinvalue = param.asInt();
  digitalWrite(pump1,pinvalue);
  } 
BLYNK_WRITE(V2){
  int pinvalue = param.asInt();
  digitalWrite(pump2,pinvalue);
  }
BLYNK_WRITE(V3){
  int pinvalue = param.asInt();
  digitalWrite(pump3,pinvalue);
  }
BLYNK_WRITE(V5){
  int pinvalue = param.asInt();
  digitalWrite(pump4,pinvalue);
  }   
  void getSendData()
{
  DS18B20.requestTemperatures(); 
  temp = DS18B20.getTempCByIndex(0); // Celcius
   Fahrenheit = DS18B20.toFahrenheit(temp); // Fahrenheit
  //Serial.println(temp);
  //Serial.println(Fahrenheit);
  Blynk.virtualWrite(V4, temp); //virtual pin V3
  //Blynk.virtualWrite(V4, Fahrenheit); //virtual pin V4
}  
  

void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(ledpin,OUTPUT);
  pinMode(pump1,OUTPUT);
  pinMode(pump2,OUTPUT);
  pinMode(pump3,OUTPUT);
  pinMode(pump4,OUTPUT);
  digitalWrite(ledpin,LOW);
  digitalWrite(pump1,HIGH);
  digitalWrite(pump2,HIGH);
  digitalWrite(pump3,HIGH);
  digitalWrite(pump4,HIGH);

  BlynkEdgent.begin();
  DS18B20.begin();
  timer.setInterval(10000L, getSendData);
}

void loop() {
  timer.run();
  BlynkEdgent.run();
}
