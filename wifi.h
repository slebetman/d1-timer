#include <ESP8266WiFi.h>

IPAddress local_IP(192, 168, 0, 1);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

class Wifi {
  public:
    void initAP (const char *ssid) {
      WiFi.mode(WIFI_AP);

      WiFi.softAPConfig(local_IP, gateway, subnet);

      WiFi.softAP(ssid);

      Serial.println("");
      Serial.print("IP address = ");
      Serial.println(WiFi.softAPIP());
    }

    void initClient (const char *ssid, const char *pass) {
      Serial.println();
      Serial.print("Connecting to ");
      Serial.println(ssid);

      WiFi.begin(ssid, pass);

      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }

      Serial.println("");
      Serial.println("WiFi connected!");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    }
};