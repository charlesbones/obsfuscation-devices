/*===================
This sketch connects to the mosquitto test broker
and ask for 3 specific values coming from the Arduino Yun.
Then everytime a message matchs with this topics, processing prints
the topic and the payload of the message in the console
==================*/
//The library used for this test can be found here: https://github.com/256dpi/processing-mqtt
import mqtt.*;

MQTTClient client;

void setup() {
  client = new MQTTClient(this);
  client.connect("mqtt://test.mosquitto.org", "processing");
  client.subscribe("/kitchen/tempeture");
  client.subscribe("/kitchen/light");
  client.subscribe("/kitchen/humidity");
}

void draw() {
}

void messageReceived(String topic, byte[] payload) {
  println("new message: " + topic + " - " + new String(payload));
}