#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <map>

const char* ssid = "IoT";
const char* password = "QAZwsxEDC@123";
const char* serverName = "http://192.168.8.132:8080";

const int SCAN_TIME = 5; // seconds
const int SEND_INTERVAL = 30; // seconds

BLEScan* pBLEScan;
std::map<std::string, std::vector<BLEAdvertisedDevice>> blePackets;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    // Add the advertised device to the map
    blePackets[advertisedDevice.getAddress().toString()].push_back(advertisedDevice);
  }
};

void wifiTask(void* pvParameters) {
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  while (true) {
    // Wait for the specified interval
    delay(SEND_INTERVAL * 1000);

    // Create a JSON object
    JsonDocument doc;
    doc["mac"] = WiFi.macAddress();
    doc["count"] = 0;
    JsonArray packetsArray = doc["packets"].to<JsonArray>();

    for (auto const& packet : blePackets) {
      std::string address = packet.first;
      std::vector<BLEAdvertisedDevice> devices = packet.second;
      int count = devices.size();
      int midRSSI = 0;

      for (auto const& device : devices) {
        midRSSI += const_cast<BLEAdvertisedDevice&>(device).getRSSI();
      }
      midRSSI /= count;

      JsonObject packetObj = packetsArray.add<JsonObject>();
      packetObj["address"] = address;
      packetObj["count"] = count;
      packetObj["RSSI"] = midRSSI;

      doc["count"] = doc["count"].as<int>() + count;
    }

    // Serialize the JSON object to a string
    String jsonString;
    serializeJson(doc, jsonString);

    // Send HTTP POST request
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

    // Clear the BLE packets map
    blePackets.clear();
  }
}

void setup() {
  Serial.begin(115200);

  // Create a task for handling Wi-Fi and HTTP POST on core 0
  xTaskCreatePinnedToCore(
    wifiTask,
    "WiFiTask",
    10000,
    NULL,
    1,
    NULL,
    0
  );

  // Initialize BLE on core 1
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}

void loop() {
  // Perform BLE scan on core 1
  BLEScanResults foundDevices = pBLEScan->start(SCAN_TIME, false);
  pBLEScan->clearResults();
}