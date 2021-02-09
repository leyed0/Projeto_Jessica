#include <ThingSpeak.h>

unsigned long myChannelNumber = 1299994;
const char * myWriteAPIKey = "PXVD10AEJS7C1S3D";
#include <ESP8266WiFi.h>

char ssid[] = "Leyed";   // your network SSID (name)
char pass[] = "syndra0812";   // your network password
int keyIndex = 0;            // your network key index number (needed only for WEP)
WiFiClient  client;

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.mode(WIFI_STA);

  ThingSpeak.begin(client);
}

void loop() {

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  // Measure Signal Strength (RSSI) of Wi-Fi connection
  long rssi = WiFi.RSSI();

  // Write value to Field 1 of a ThingSpeak Channel
  for(int i=0; i<100;i++){
    int httpCode = ThingSpeak.writeField(myChannelNumber, 1, i*i, myWriteAPIKey);

    if (httpCode == 200) {
      Serial.println("Channel write successful.");
    }
    else {
      Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
    }
    // Wait 20 seconds to update the channel again
    delay(15000);
  }
}
