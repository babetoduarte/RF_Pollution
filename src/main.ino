#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP.h>

//Function prototypes
void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

//Define AP SSID and Password
const char* ssid = "J4D_RPi";
const char* password = "RaspberryPi";

//Client and Server Attributes
IPAddress server(192,168,42,1);
WiFiClient espClient;
PubSubClient client(espClient);

//Message attributes
long lastMsg = 0;
char msg[50];
int value =0;

void setup(){
    pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
    Serial.begin(115200);
    setup_wifi();
    client.setServer(server, 1883);
    client.setCallback(callback);
}

void loop(){
    if (!client.connected()) {
      reconnect();
    }
    client.loop();

    long now = millis();
    if (now - lastMsg > 2000) {
      lastMsg = now;
      ++value;
      snprintf (msg, 75, "hello world #%ld", value);
      Serial.print("Publish message: ");
      Serial.println(msg);
      client.publish("outTopic", msg);
    }
}

void setup_wifi(){
    //Wait a bit
    delay(10);
    //Print AP SSID
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    //Begin WiFi Connection
    WiFi.begin(ssid, password);
    //Print .... while awaiting connection
    while(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }
    //Print Connection Information
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length){
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++){
        Serial.print((char)payload[i]);
    }
    Serial.println();

    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1') {
      digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
      // but actually the LED is on; this is because
      // it is acive low on the ESP-01)
    } else {
      digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
    }
}

void reconnect(){
    // Loop until we're reconnected
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      // Attempt to connect
      if (client.connect("ESP8266Client")) {
        Serial.println("connected");
        // Once connected, publish an announcement...
        client.publish("outTopic", "hello world");
        // ... and resubscribe
        client.subscribe("inTopic");
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
}

void sleep(int timeInSeconds){
    ESP.deepSleep(timeInSeconds * 1000000);
}
