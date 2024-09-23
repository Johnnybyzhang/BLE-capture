#include "my_advertised_device_callbacks.h"

void MyAdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice) {
  // Convert BLEAdvertisedDevice to AdvertisedDeviceBarebone
  AdvertisedDeviceBarebone bareboneDevice(advertisedDevice);
  // Add the barebone advertised device to the map
  blePackets[bareboneDevice.getAddress()].push_back(bareboneDevice);
}