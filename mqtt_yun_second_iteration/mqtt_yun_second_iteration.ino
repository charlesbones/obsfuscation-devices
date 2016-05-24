/*This scketch uses 3 different sensor:
 * Grove - Temperature and Humidity Sensor: http://www.seeedstudio.com/wiki/Grove_-_Temperature_and_Humidity_Sensor
 * Grove - Digital Light Sensor: http://www.seeedstudio.com/wiki/Grove_-_Digital_Light_Sensor
 * PIR Motion sensor: http://www.electrokit.com/en/pir-motion-sensor.45479
 * 
 * Also a push button and an Oled screen http://www.seeedstudio.com/wiki/Grove_-_OLED_Display_0.96%22
 * With them 3 values (light, humidity and temperature)  will be send mySql database using a PHP API
 * then this value while the visualize in a graph build in p5.js
 */
#include <Bridge.h>
#include <SeeedOLED.h>
#include <Digital_Light_TSL2561.h>
#include <DHT.h>
#include <Wire.h>

#define DHTPIN A0
#define DHTTYPE DHT11
const int buttonPin = A1;
const int ledPin =  12;
int sensorPin = A2;

DHT dht(DHTPIN, DHTTYPE);

int buttonState = 0;
int sensorState = 0;
int pirState = LOW;
int randomState=LOW;

float currentPir;
int counterPir;

float currentButton;
int counterButton;
void setup()
{
  Bridge.begin();
  Console.begin();
  Wire.begin();

  dht.begin();
  TSL2561.init();
  SeeedOled.init();
  //DDRB |= 0x21;
  //PORTB |= 0x21;

  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);

  SeeedOled.clearDisplay();
  SeeedOled.setInverseDisplay();
  SeeedOled.setPageMode();
  SeeedOled.setTextXY(0, 0);
  SeeedOled.putString("Hi, How are you?");

  currentPir = millis();
  currentButton = millis();
}

void loop()
{
  counterPir = (millis() - currentPir) / 1000;
  counterButton = (millis() - currentButton) / 1000;

  buttonState = digitalRead(buttonPin);
  sensorState = digitalRead(sensorPin);
  //Console.println(sensorState);
  debug();
  if ((buttonState == LOW)&&(randomState==LOW)) {
    randomPhp();
    randomState=HIGH;
    //digitalWrite(ledPin, HIGH);
    /*SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString("I just sent the ");
    SeeedOled.setTextXY(0, 30);
    SeeedOled.putString("data, thank you ");
    SeeedOled.setTextXY(0, 60);
    SeeedOled.putString("for disturbing me!!");*/
    /*if(counter>10){
      SeeedOled.setTextXY(0, 0);
      SeeedOled.putString("Hi, How are you?");
    }*/
  } 
  if (randomState == HIGH) {
    counterButton = (millis() - currentButton) / 1000;
    digitalWrite(ledPin,HIGH);
    if (counterButton > 60) {
      randomState = LOW;
      digitalWrite(ledPin, LOW);
      currentButton=millis();
    }
  }
  
  if ((sensorState == LOW)&&(pirState==LOW)) {
    runPhp();
    pirState=HIGH;
  }
  if (pirState == HIGH) {
    counterPir = (millis() - currentPir) / 1000;
    digitalWrite(ledPin,HIGH);
    if (counterPir > 60) {
      pirState = LOW;
      digitalWrite(ledPin, LOW);
      currentPir=millis();
    }
  }

}
void randomPhp(){
  Process sub;
  sub.begin("php-cli");
  sub.addParameter("/mnt/sda1/substitution.php");
  sub.run();
  delay(1000);
}
void runPhp() {
  Process p;
  p.begin("php-cli");
  p.addParameter("/mnt/sda1/db.php");
  p.addParameter(String(dht.readTemperature()));
  p.addParameter(String(dht.readHumidity()));
  p.addParameter(String(TSL2561.readVisibleLux()));
  p.run();
  delay(1000);
}
void debug() {
  Console.print("Tempeture: ");
  Console.print(dht.readTemperature());
  Console.print(" --- ");
  Console.print("Humidity: ");
  Console.print(dht.readHumidity());
  Console.print(" --- ");
  Console.print("Light: ");
  Console.print(TSL2561.readVisibleLux());
  Console.print(" --- ");
  Console.print("Button: ");
  Console.print(buttonState);
  Console.print(" --- ");
  Console.print("Sensor: ");
  Console.println(sensorState);
}

