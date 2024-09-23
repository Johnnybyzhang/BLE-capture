#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "network_task.h"
#include "advertised_device_barebone.h"

extern const char* ssid;
extern const char* password;
extern const char* serverName;
extern const int SEND_INTERVAL;
extern std::map<std::string, std::vector<AdvertisedDeviceBarebone>> blePackets;

class WiFiTask : public NetworkTask {
public:
  void connect() override {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
  }

  void sendData() override {
    while (true) {
      delay(SEND_INTERVAL * 1000);

      JsonDocument response;
      response["mac"] = WiFi.macAddress();
      response["count"] = 0;
      JsonArray packetsArray = response["packets"].to<JsonArray>();

      for (auto const& packet : blePackets) {
        std::string address = packet.first;
        std::vector<AdvertisedDeviceBarebone> devices = packet.second;
        int count = devices.size();
        int midRSSI = 0;

        if (count > 1) {
          for (auto const& device : devices) {
            midRSSI += device.getRSSI();
          }
          midRSSI /= count;

          JsonObject packetObj = packetsArray.add<JsonObject>();
          packetObj["address"] = address;
          packetObj["count"] = count;
          packetObj["RSSI"] = midRSSI;

          response["count"] = response["count"].as<int>() + count;
        }
      }

      String jsonString;
      serializeJson(response, jsonString);

      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST(jsonString);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("HTTP POST successful");
        Serial.println("Response: " + response);
      } else {
        Serial.println("HTTP POST failed");
      }

      http.end();
      blePackets.clear();
    }
  }
};