#ifndef MY_ADVERTISED_DEVICE_CALLBACKS_H
#define MY_ADVERTISED_DEVICE_CALLBACKS_H

#include <BLEAdvertisedDevice.h>
#include <map>
#include <vector>
#include "advertised_device_barebone.h"

extern std::map<std::string, std::vector<AdvertisedDeviceBarebone>> blePackets;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice);
};

#endif // MY_ADVERTISED_DEVICE_CALLBACKS_H