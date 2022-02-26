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

## Setup Google Cloud Platform for IoT devices. The instruction from [here](https://github.com/GoogleCloudPlatform/google-cloud-iot-arduino)

Enable the Cloud IoT Core API by opening the [Google Cloud IoT Core console](https://console.cloud.google.com/iot/).
Next, create your device registry as described in [the Quickstart](https://cloud.google.com/iot/docs/quickstart) or by using the [Google Cloud SDK](https://cloud.google.com/sdk).

If you're using the SDK, the following commands will setup PubSub and Cloud IoT
Core for testing on your Arduino device:

Create the PubSub topic and subscription:

    gcloud pubsub topics create atest-pub --project=YOUR_PROJECT_ID
    gcloud pubsub subscriptions create atest-sub --topic=atest-pub

Create the Cloud IoT Core registry:

    gcloud iot registries create atest-registry \
      --region=us-central1 --event-notification-config=topic=atest-pub

Generate an Elliptic Curve (EC) private / public key pair:

    openssl ecparam -genkey -name prime256v1 -noout -out ec_private.pem
    openssl ec -in ec_private.pem -pubout -out ec_public.pem

Register the device using the keys you generated:

    gcloud iot devices create atest-dev --region=us-central1 \
        --registry=atest-registry \
        --public-key path=ec_public.pem,type=es256

At this point, your registry is created and your device has been added to the
registry so you're ready to connect it.

Find and replace the following values first:
* Project ID (get from console or `gcloud config list`)
* Location (default is `us-central1`)
* Registry ID (created in previous steps, e.g. `atest-reg`)
* Device ID (created in previous steps, e.g. `atest-device`)

You will also need to extract your private key using the following command:

    openssl ec -in ec_private.pem -noout -text

... and will need to copy the output for the private key bytes into the private
key string in your Arduino project.

When you run the sample, the device will connect and receive configuration
from Cloud IoT Core. When you change the configuration in the Cloud IoT Core
console, that configuration will be reflected on the device.

Before the examples will work, you will also need to configure the root
certificate as described in the configuration headers.

After you have published telemetry data, you can read it from the PubSub topic
using the [Google Cloud SDK](https://cloud.google.com/sdk). With the SDK installed,
run the following command to create a :

```
gcloud pubsub subscriptions create <your-subscription-name> --topic=<your-iot-pubsub-topic>
```

Then read the telemetry messages:
```
gcloud pubsub subscriptions pull --limit 500 --auto-ack <your-subscription-name>
```

---

Feel free to write any suggestions.
