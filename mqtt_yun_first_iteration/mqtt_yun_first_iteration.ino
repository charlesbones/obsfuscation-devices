/*This scketch uses 2 different sensor:
 * Grove - Temperature and Humidity Sensor: http://www.seeedstudio.com/wiki/Grove_-_Temperature_and_Humidity_Sensor
 * Grove - Digital Light Sensor: http://www.seeedstudio.com/wiki/Grove_-_Digital_Light_Sensor
 * 
 * With them 3 values (light, humidity and temperature)  will be send to the mosquitto test broker then this information 
 * will be read by Processing.
 */
 
//Sensor Libraries
#include <Digital_Light_TSL2561.h>
#include <DHT.h>
//SPI and I2C libraries
#include <Wire.h>
#include <SPI.h>
//Arduino Yun libraries
#include <Bridge.h>
#include <Console.h>
#include <YunClient.h>
#include <PubSubClient.h>

#define DHTPIN A0
#define DHTTYPE DHT11
#define LED 13

YunClient ethClient;
PubSubClient client("85.119.83.194", 1883, ethClient);

DHT dht(DHTPIN, DHTTYPE);

float current;
int counter;

void setup()
{
  Wire.begin();
  Bridge.begin();
  //Console.begin();
  //while (!Console);

  dht.begin();
  TSL2561.init();

  current = millis();
  pinMode(LED,OUTPUT);
}
char* hArray;
char* tArray;
char* lArray;

char message_buffer[100];
void loop()
{
  counter = (millis() - current) / 1000;
  //Console.println(counter);
  if (counter > 10) {
    current = millis();
    if (client.connect("arduinoClient")) {
      hArray = dtostrf(dht.readHumidity(), 5, 2, message_buffer);
      client.publish("/kitchen/humidity", hArray);

      tArray = dtostrf(dht.readTemperature(), 5, 2, message_buffer);
      client.publish("/kitchen/tempeture", tArray);

      lArray = dtostrf(TSL2561.readVisibleLux(), 5, 2, message_buffer);
      client.publish("/kitchen/light", lArray);
    }
    client.loop();
  }
}
