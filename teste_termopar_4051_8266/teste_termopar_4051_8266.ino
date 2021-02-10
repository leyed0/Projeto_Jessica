#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "max6675.h"

const char* ssid = "tixx";        // WiFi name
const char* password = "12345678";    // WiFi password
const char* mqtt_server = "mqtt.cloud.kaaiot.com";
const String TOKEN = "espp";        // Endpoint token - you get (or specify) it during device provisioning
const String APP_VERSION = "c0hdeg7b6q8e07efti7g-v2";  // Application version - you specify it during device provisioning

const unsigned long fiveSeconds = 1 * 2 * 1000UL;
static unsigned long lastPublish = 0 - fiveSeconds;

WiFiClient espClient;
PubSubClient client(espClient);

struct CD4051
{
    uint8_t A, B, C;
    int Val;
};

CD4051 CD;

MAX6675 robojax(16, 5, 4);// create instance object of MAX6675
void setup() {
  InitCD(14,12,13);
  Serial.begin(115200);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  setup_wifi();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastPublish >= fiveSeconds) {
    lastPublish += fiveSeconds;

    digitalWrite(LED_BUILTIN, LOW);
    DynamicJsonDocument telemetry(1023);
    telemetry.createNestedObject();
    for (int i = 0; i < 8; i++)
    {
        SetCd(i);
        float temp = robojax.readCelsius();
        telemetry[0][String(i)] = temp;
        Serial.print(i);
        Serial.print(" - C = ");
        Serial.println(temp);
    }
    String topic = "kp1/" + APP_VERSION + "/dcx/" + TOKEN + "/json";
    client.publish(topic.c_str(), telemetry.as<String>().c_str());
    Serial.println("Published on topic: " + topic);
    digitalWrite(LED_BUILTIN, HIGH);
  }

}
void InitCD(uint8_t a,uint8_t b, uint8_t c){
  CD.A = a;
  CD.B = b;
  CD.C = c;
  pinMode(CD.A, OUTPUT);
  pinMode(CD.B, OUTPUT);
  pinMode(CD.C, OUTPUT);
  digitalWrite(CD.A, LOW);
  digitalWrite(CD.B, LOW);
  digitalWrite(CD.C, LOW);
}

void SetCd(int val){
  CD.Val = val;
  digitalWrite(CD.A, bitRead(val, 0));
  digitalWrite(CD.B, bitRead(val, 1));
  digitalWrite(CD.C, bitRead(val, 2));
  delay(20);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.printf("\nHandling command message on topic: %s\n", topic);

  DynamicJsonDocument doc(1023);
  deserializeJson(doc, payload, length);
  JsonVariant json_var = doc.as<JsonVariant>();

  DynamicJsonDocument commandResponse(1023);
  for (int i = 0; i < json_var.size(); i++) {
    unsigned int command_id = json_var[i]["id"].as<unsigned int>();
    commandResponse.createNestedObject();
    commandResponse[i]["id"] = command_id;
    commandResponse[i]["statusCode"] = 200;
    commandResponse[i]["payload"] = "done";
  }

  String responseTopic = "kp1/" + APP_VERSION + "/cex/" + TOKEN + "/result/SWITCH";
  client.publish(responseTopic.c_str(), commandResponse.as<String>().c_str());
  Serial.println("Published response to SWITCH command on topic: " + responseTopic);
}

void setup_wifi() {
  if (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.println();
    Serial.printf("Connecting to [%s]", ssid);
    WiFi.begin(ssid, password);
    connectWiFi();
  }
}

void connectWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    char *client_id = "client-id-123ab";
    if (client.connect(client_id)) {
      Serial.println("Connected to WiFi");
      // ... and resubscribe
      subscribeToCommand();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void subscribeToCommand() {
  String topic = "kp1/" + APP_VERSION + "/cex/" + TOKEN + "/command/SWITCH/status";
  client.subscribe(topic.c_str());
  Serial.println("Subscribed on topic: " + topic);
}