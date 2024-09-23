#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include "advertised_device_barebone.h"
#include "my_advertised_device_callbacks.h"
#include "network_task.h"
#include "wifi_task.cpp" // 包含 WiFiTask 类

const char* ssid = "IoT";
const char* password = "QAZwsxEDC@123";
const char* serverName = "http://192.168.8.132:8000/api/jsondata/";
const int SEND_INTERVAL = 30; // seconds
BLEScan* pBLEScan;
std::map<std::string, std::vector<AdvertisedDeviceBarebone>> blePackets;

NetworkTask* networkTask;

void setup() {
  Serial.begin(115200);

  // 创建 WiFiTask 实例
  networkTask = new WiFiTask();
  networkTask->connect();

  // 创建一个任务来处理网络数据发送
  xTaskCreatePinnedToCore(
    [](void* pvParameters) {
      networkTask->sendData();
    },
    "NetworkTask",
    60000,
    NULL,
    1,
    NULL,
    0
  );

  // 初始化 BLE
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}

void loop() {
  // 执行 BLE 扫描
  BLEScanResults foundDevices = pBLEScan->start(5, false);
  pBLEScan->clearResults();
}