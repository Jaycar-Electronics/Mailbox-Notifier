#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// -----------------------------------------------
// -----------------------------------------------

const char *wifi_ssid = "NAME";
const char *wifi_pass = "password"; 

#define TRIGGER_NAME  "ESP_reset"
#define TRIGGER_KEY   "maker key"

// -----------------------------------------------
// -----------------------------------------------

const char *ifttt_url = "https://maker.ifttt.com"
          "/trigger/"
          TRIGGER_NAME
          "/with/key/"
          TRIGGER_KEY;

BearSSL::WiFiClientSecure client;

void setup() {
  connectToWiFi(wifi_ssid, wifi_pass);
  sendNotification();
  Serial.println("Goodnight!");
  ESP.deepSleep(0);
}

void loop() {}


// =========================================================
// =========================================================

void connectToWiFi(const char * ssid, const char * pass){
  Serial.begin(115200);
  WiFi.begin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected!");
  Serial.printf("Network: %s\n", wifi_ssid);
  Serial.printf("IP: %s\n", WiFi.localIP().toString().c_str());
  client.setInsecure();
}

void sendNotification()
{
  // should only be called when wanting to send a notification
  HTTPClient http;
  http.begin(client, ifttt_url);
  int r = http.GET();

  if (r < 0)
  {
    Serial.println(http.errorToString(r));
  }
  else
  {
    http.writeToStream(&Serial);
    Serial.println();
  }
  http.end();
}
