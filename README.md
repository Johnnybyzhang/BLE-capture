# BLE Capture for Privacy-Preserving Room Occupancy Estimation

This repository contains the source code and resources for **Privacy-Preserving Room Occupancy Estimation Using Federated Analytics of BLE Packets**, a demonstration project that achieves 95% accuracy in occupancy estimation while preserving user privacy.

## Abstract

We present a privacy-preserving method for estimating room occupancy using BLE (Bluetooth Low Energy) packets. By leveraging federated analytics, the system processes data locally, sharing only aggregated device counts, thus protecting user privacy. The approach provides a cost-effective and accurate alternative to traditional methods such as PIR or mmWave-based sensors.

The repository includes the code to:

- Capture BLE packets
- Perform packet filtering based on RSSI and MAC whitelisting
- Aggregate device counts
- Demonstrate occupancy estimation

## System Overview

### Equipment
- **ESP32-S3** Development Board
- **BLE Packet Capture**: Continuous capture and filtering of BLE packets using RSSI thresholds and MAC address whitelisting.
- **Reporting**: Aggregate and report device counts without exposing individual device details.

### Key Features
- **Privacy-Preserving**: No decoding of BLE payloads; only aggregated counts are transmitted.
- **Accurate Occupancy Prediction**: Using BLE packet count thresholds, our approach achieves 95% accuracy.
- **Federated Analytics**: The system processes data locally to reduce the risk of exposing sensitive information.

## Installation

### Prerequisites

- **ESP32-S3 Development Board**
- **PlatformIO**
- **BLE-capable devices** to test the occupancy estimation

### Setup

1. Clone this repository:
   ```bash
   git clone https://github.com/Johnnybyzhang/BLE-capture.git
   cd BLE-capture
   ```

2. Install dependencies for PlatformIO:
   ```bash
   platformio init
   platformio run
   ```

3. Flash the code to the ESP32-S3 board.

### Configuration

- **MAC Whitelist**: Update the `whitelist` in the code to filter out virtual addresses or devices you don't want to track.
- **RSSI Threshold**: Adjust the `RSSI_THRESHOLD` value to fine-tune packet filtering for your environment.

## Usage

Once the ESP32-S3 is set up, it will continuously capture BLE packets, filter them by RSSI and MAC address, and aggregate the number of unique devices detected.

The device counts are then reported at regular intervals, simulating room occupancy.

### Commands

- **Start Packet Capture**: The system automatically starts capturing BLE packets on boot.
- **Stop Packet Capture**: Use the reset button or power off the device.

## Future Work

Future enhancements will include:

1. Extending the system to multi-room setups.
2. Improving the accuracy with longer testing durations.
3. Exploring advanced privacy protection techniques within federated analytics.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact

For any questions or inquiries, please contact:

- Boyan Zhang | boyan.zhang@dukekunshan.edu.cn
