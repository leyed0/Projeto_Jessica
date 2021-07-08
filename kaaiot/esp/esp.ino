#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

const char* ssid = "Vivo_AP_1";        // WiFi name
const char* password = "4130240554";    // WiFi password
//const char* ssid = "Leyed";        // WiFi name
//const char* password = "syndra0812";    // WiFi password
const char* mqtt_server = "mqtt.cloud.kaaiot.com";
const String TOKEN = "ESP_0";        // Endpoint token - you get (or specify) it during device provisioning
const String TOKEN1 = "ESP_1";        // Endpoint token - you get (or specify) it during device provisioning
const String TOKEN2 = "ESP_2";        // Endpoint token - you get (or specify) it during device provisioning
const String APP_VERSION = "c11qdq2rqa51q5h5slkg-v1";  // Application version - you specify it during device provisioning

struct readings{
    //uint8_t ID;
    uint8_t Continuity;
    uint8_t Moisture;
    //uint8_t chk;
    uint16_t Thermal[5];
};

WiFiClient espClient;
PubSubClient client(espClient);
readings Read[3];

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.begin(115200);
  setup_wifi();
  digitalWrite(LED_BUILTIN, HIGH);
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
            Serial.print((float)Read[j].Thermal[i]/100, 1);
            Serial.print("\t");
        }
        //String tmp = String((Read[j].Continuity & 1)?'0':'1')+ String((Read[j].Continuity & 2)?'0':'1')+ String((Read[j].Continuity & 4)?'0':'1')+ String((Read[j].Continuity & 8)?'0':'1')+ String((Read[j].Continuity & 16)?'0':'1');
        //Serial.print(tmp);
        //Serial.print(Read[j].Continuity, BIN);
        //Serial.print("\t");
        Serial.print(Read[j].Moisture);
        Serial.print("\t ");
    }
    Serial.println();
}

bool ReceiveData(){
  char* dp = (char*) &Read;
  if(Serial.available()){
    //Serial.println("AV");
  if(Serial.read()=='W')
  {
    do{
      delay(2);
    }while(Serial.available()<sizeof(Read));
    for (int i = 0; i < (sizeof(Read)); i++) *dp++ = Serial.read();
    //Serial.read();
    //Serial.flush();
    // readings temp;
    //   char* dp = (char*) &temp;
    //   for (int i = 0; i < (sizeof(readings)); i++) *dp++ = Serial.read();
    //   switch (temp.ID)
    //   {
    //   case 0:
    //     Read[0] = temp;
    //     break;
    //   case 1:
    //     Read[1] = temp;
    //     break;
    //   case 2:
    //     Read[2] = temp;
    //     break;
    //   default:
    //     break;
    //   }
    //   Serial.read();
     return true;
  }
  }
  return false;
}

void UploadData(){
  setup_wifi();
  if (!client.connected()) {
    reconnect();
  }
  digitalWrite(LED_BUILTIN, LOW);
  client.loop();
  DynamicJsonDocument telemetry(1023);
  DynamicJsonDocument telemetry1(1023);
  DynamicJsonDocument telemetry2(1023);
  telemetry.createNestedObject();
  telemetry[0]["T1"] = (float)Read[0].Thermal[0]/100;
  telemetry[0]["T2"] = (float)Read[0].Thermal[1]/100;
  telemetry[0]["T3"] = (float)Read[0].Thermal[2]/100;
  telemetry[0]["T4"] = (float)Read[0].Thermal[3]/100;
  telemetry[0]["T5"] = (float)Read[0].Thermal[4]/100;
  telemetry[0]["CNT"] = Read[0].Continuity;
  telemetry[0]["Moist"] = (float)map(Read[0].Moisture,0,255,0,100);
  
  telemetry1[0]["T1"] = (float)Read[1].Thermal[0]/100;
  telemetry1[0]["T2"] = (float)Read[1].Thermal[1]/100;
  telemetry1[0]["T3"] = (float)Read[1].Thermal[2]/100;
  telemetry1[0]["T4"] = (float)Read[1].Thermal[3]/100;
  telemetry1[0]["T5"] = (float)Read[1].Thermal[4]/100;
  telemetry1[0]["CNT"] = Read[1].Continuity;
  telemetry1[0]["Moist"] = (float)map(Read[1].Moisture,0,255,0,100);
  
  telemetry2[0]["T1"] = (float)Read[2].Thermal[0]/100;
  telemetry2[0]["T2"] = (float)Read[2].Thermal[1]/100;
  telemetry2[0]["T3"] = (float)Read[2].Thermal[2]/100;
  telemetry2[0]["T4"] = (float)Read[2].Thermal[3]/100;
  telemetry2[0]["T5"] = (float)Read[2].Thermal[4]/100;
  telemetry2[0]["CNT"] = Read[2].Continuity;
  telemetry2[0]["Moist"] = (float)map(Read[2].Moisture,0,255,0,100);

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
  digitalWrite(LED_BUILTIN, LOW);
  if (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.println();
    Serial.printf("Connecting to [%s]", ssid);
    WiFi.begin(ssid, password);
    connectWiFi();
  }
  digitalWrite(LED_BUILTIN, HIGH);
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
