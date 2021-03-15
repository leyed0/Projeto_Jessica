#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

const char* ssid = "Vivo_AP_1";        // WiFi name
const char* password = "4130240554";    // WiFi password
const char* mqtt_server = "mqtt.cloud.kaaiot.com";
const String TOKEN = "ESP_0";        // Endpoint token - you get (or specify) it during device provisioning
const String TOKEN1 = "ESP_1";        // Endpoint token - you get (or specify) it during device provisioning
const String TOKEN2 = "ESP_2";        // Endpoint token - you get (or specify) it during device provisioning
const String APP_VERSION = "c11qdq2rqa51q5h5slkg-v1";  // Application version - you specify it during device provisioning

struct readings{
    uint8_t Continuity;
    uint8_t Moisture;
    uint8_t chk;
    uint8_t Thermal[5];
};

WiFiClient espClient;
PubSubClient client(espClient);
readings Read[3];

void setup() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.begin(115200);
  Serial.println("setup");
  setup_wifi();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();


  if(ReceiveData()){
    Printdata();
    UploadData();
  }
}

void Printdata(){
  for (uint8_t j = 0; j < 3; j++)
    {
        Serial.print(j);
        Serial.print(": ");
        Serial.print("\t");
        for (uint8_t i = 0; i < 5; i++)
        {
            Serial.print((float)Read[j].Thermal[i]/10, 1);
            Serial.print("\t");
        }
        Serial.print(Read[j].Continuity, BIN);
        Serial.print("\t");
        Serial.print(Read[j].Moisture);
        Serial.print("\t ");
    }
    Serial.println();
}

bool ReceiveData(){
  if (Serial.available()>=(sizeof(readings)*3))
    {
        char* dp = (char*) &Read;
        for (int i = 0; i < (sizeof(readings)*3); i++) *dp++ = Serial.read();
        Serial.read();
        return true;
    }
    return false;
}

void UploadData(){
  setup_wifi();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  DynamicJsonDocument telemetry(1023);
  DynamicJsonDocument telemetry1(1023);
  DynamicJsonDocument telemetry2(1023);
  telemetry.createNestedObject();
  telemetry[0]["T1"] = (float)Read[0].Thermal[0]/10;
  telemetry[0]["T2"] = (float)Read[0].Thermal[1]/10;
  telemetry[0]["T3"] = (float)Read[0].Thermal[2]/10;
  telemetry[0]["T4"] = (float)Read[0].Thermal[3]/10;
  telemetry[0]["T5"] = (float)Read[0].Thermal[4]/10;
  
  telemetry1[0]["T1"] = (float)Read[1].Thermal[0]/10;
  telemetry1[0]["T2"] = (float)Read[1].Thermal[1]/10;
  telemetry1[0]["T3"] = (float)Read[1].Thermal[2]/10;
  telemetry1[0]["T4"] = (float)Read[1].Thermal[3]/10;
  telemetry1[0]["T5"] = (float)Read[1].Thermal[4]/10;
  
  telemetry2[0]["T1"] = (float)Read[2].Thermal[0]/10;
  telemetry2[0]["T2"] = (float)Read[2].Thermal[1]/10;
  telemetry2[0]["T3"] = (float)Read[2].Thermal[2]/10;
  telemetry2[0]["T4"] = (float)Read[2].Thermal[3]/10;
  telemetry2[0]["T5"] = (float)Read[2].Thermal[4]/10;

  String topic = "kp1/" + APP_VERSION + "/dcx/" + TOKEN + "/json";
  String topic1 = "kp1/" + APP_VERSION + "/dcx/" + TOKEN1 + "/json";
  String topic2 = "kp1/" + APP_VERSION + "/dcx/" + TOKEN2 + "/json";

  digitalWrite(LED_BUILTIN, LOW);
  client.publish(topic.c_str(), telemetry.as<String>().c_str());
  client.publish(topic1.c_str(), telemetry1.as<String>().c_str());
  client.publish(topic2.c_str(), telemetry2.as<String>().c_str());
  //Serial.println("Published on topic: " + topic);
  digitalWrite(LED_BUILTIN, HIGH);
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