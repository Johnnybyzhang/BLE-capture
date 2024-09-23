#include "advertised_device_barebone.h"

AdvertisedDeviceBarebone::AdvertisedDeviceBarebone(BLEAdvertisedDevice device) {
  address = device.getAddress().toString();
  rssi = device.getRSSI();
}

std::string AdvertisedDeviceBarebone::getAddress() const {
  return address;
}

int AdvertisedDeviceBarebone::getRSSI() const {
  return rssi;
}