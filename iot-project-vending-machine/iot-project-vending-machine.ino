#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1 // Reset pin #
#define SCREEN_ADDRESS 0x3C 
Adafruit_SH1106 display(OLED_RESET);

const char  *SSID = "iPhoneGurru";    // SSID of your WiFi
const char  *PASSWORD = "12345678";    // Password of your WiFi
const char  *mqqttBroker = "test.mosquitto.org";
const int   mqttPort = 1883;
const char  *mqttClientID = "NodeMCU1234";

const char  *queryTopic = "Code-red1/Query"; // Topic for Queries to the server
const char  *purchaseTopic = "Code-red1/Purchase"; // Topic for purchases
const char  *resupplyTopic = "Code-red1/Resupply"; // Topic for purchases

WiFiClient      espClient;
PubSubClient    mqttClient(espClient);

void mqttInit() {
    mqttClient.setServer(mqqttBroker, mqttPort);
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void mqttLoop() {
    while (!mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (mqttClient.connect(mqttClientID)) {
          Serial.println("connected");
        }
        else if (WiFi.status() != WL_CONNECTED){
          Serial.print("Wifi connection failed");
          Serial.println(" try again in 5 seconds");
          delay(5000);
        } 
        else {
          Serial.print("failed, rc=");
          Serial.print(mqttClient.state());
          Serial.println(" try again in 5 seconds");
          delay(5000);
        }
    }
    mqttClient.loop();
}



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
