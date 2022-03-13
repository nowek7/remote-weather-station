# Remote weather station

## Description

Simple (remote) weather station which send data directly to cloud storage (Google Cloud Platform) via MQTT.

More details is in the following [presentation](/docs/zdalna_stacja_pogodowa_michal_nowak.pdf). Unfortunately only in polish.

## Prerequisites

* Devices and sensors:
  - [DFRobot: FireBeetle ESP32 IOT Microcontroller(V3.0)](https://wiki.dfrobot.com/FireBeetle_ESP32_IOT_Microcontroller(V3.0)__Supports_Wi-Fi_&_Bluetooth__SKU__DFR0478)
  - [DFRobot: FireBeetle Covers-Gravity IO Expansion Shield](https://wiki.dfrobot.com/FireBeetle_Covers-Gravity_I_O_Expansion_Shield_SKU__DFR0483)
  - [Gravity BMP388 Barometric Pressure Sensor](https://wiki.dfrobot.com/Gravity_BMP280_Barometric_Pressure_Sensors_SKU_SEN0251)
  - [Gravity: Analog SHT30 Temperature & Humidity Sensor](https://wiki.dfrobot.com/Gravity:%20Analog%20SHT30%20Temp.%20&%20RH%20Sensor_SKU_DFR0588)
  - [Gravity: Analog Ambient Light Sensor](https://wiki.dfrobot.com/DFRobot_Ambient_Light_Sensor_SKU_DFR0026)
  - [Gravity: Analog Grayscale Sensor](https://wiki.dfrobot.com/Analog_Grayscale_Sensor_V2_SKU_DFR0022)

* Arduino software
  - [MQTT library](https://www.arduino.cc/reference/en/libraries/mqtt/)
  - [Cooperative-multitasking library](https://www.arduino.cc/reference/en/libraries/cooperative-multitasking/)
  - [MQTT Client library](https://www.arduino.cc/reference/en/libraries/mqtt-client/)
  - [Google Cloud IOT Core JWT](externals/Google_Cloud_IoT_Core_JWT.zip)
  - [JSON library](https://www.arduino.cc/reference/en/libraries/arduinojson/)
  - [DFRobot_bmp3xx library for pressure/temperature sensor](https://www.arduino.cc/reference/en/libraries/dfrobot_bmp3xx/)
* C++14
* Python >= 3.6.x

## How to install libraries in Arduino?

Install the library using the Arduino Library Manager.

* Open Arduino and select the **Sketch > Include Library > Library Manager**
menu item.
* In the filter box, search for the above libraries.
* Install the library

Or
* Download .zip libraries from links that are in the prerequisites section
* Open Arduino and select the **Sketch > Include Library > Add .ZIP Library...**
menu item.
* Select downloaded libraries

## How to setup config?
```bash
$ python3 .\associations_cfg.py --help
usage: associations_cfg.py [-h] [--ssid SSID] [--password PASSWORD] [--project_id PROJECT_ID] [--cloud_region CLOUD_REGION] [--registry_id REGISTRY_ID]
                           [--device_id DEVICE_ID] [--mqtt_bridge_hostname MQTT_BRIDGE_HOSTNAME] [--mqtt_bridge_port MQTT_BRIDGE_PORT]

Write config file

options:
  -h, --help            show this help message and exit
  --ssid SSID           WIFI SSID
  --password PASSWORD   WIFI password
  --project_id PROJECT_ID
                        GCP project_id
  --cloud_region CLOUD_REGION
                        GCP cloud_region
  --registry_id REGISTRY_ID
                        GCP registry_id
  --device_id DEVICE_ID
                        GCP device_id
  --mqtt_bridge_hostname MQTT_BRIDGE_HOSTNAME
                        GCP mqtt_bridge_hostname
  --mqtt_bridge_port MQTT_BRIDGE_PORT
                        GCP mqtt_bridge_port
```

```
python3 associations_cfg.py --ssid <your_ssid> --password <your_password> \
                            --project_id <your_project_id> \
                            --cloud_region <your_cloud_region> \
                            --registry_id <your_registry_id> \
                            --device_id <your_device_id>
```

The following options are optional:
  - `--mqtt_bridge_hostname` (default value: *mqtt.googleapis.com*)
  - `--mqtt_bridge_port` (default value: *8883*)


After that, one thing is remain: fill `private_key` and` root_key` variables in `config.hpp`.
In the next section, this one will be explains.

---

## Setup Google Cloud Platform for IoT devices.

The instruction is [here](https://github.com/GoogleCloudPlatform/google-cloud-iot-arduino).

---

Feel free to write any suggestions.
