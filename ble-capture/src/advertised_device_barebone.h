#ifndef ADVERTISED_DEVICE_BAREBONE_H
#define ADVERTISED_DEVICE_BAREBONE_H

#include <BLEAdvertisedDevice.h>
#include <string>

class AdvertisedDeviceBarebone {
public:
  AdvertisedDeviceBarebone(BLEAdvertisedDevice device);
  std::string getAddress() const;
  int getRSSI() const;

private:
  std::string address;
  int rssi;
};

#endif // ADVERTISED_DEVICE_BAREBONE_H