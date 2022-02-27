#pragma once

#include "gcp_config.hpp"

#include <memory>

#include <Client.h>
#include <CloudIoTCore.h>
#include <CloudIoTCoreMqtt.h>
#include <jwt.h>
#include <MQTT.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

namespace network
{
  namespace gcp
  {
    class IoTClient
    {
    public:
      /**
       * @brief Construct a new IoTClient instance
       *
       * @param config Config of Google Cloud IoT
       */
      IoTClient(const Config& config);
      IoTClient(const IoTClient&) = delete;
      IoTClient& operator=(const IoTClient&) = delete;
      ~IoTClient();

      /**
       * @brief Connect to Google Cloud IoT
       *
       */
      void connect();

      /**
       * @brief Publish data to Google Cloud IoT
       *
       * @param data Deseralized std::string data
       * @return bool
       */
      bool publish(const std::string& data);

    private:
      std::unique_ptr<WiFiClientSecure> mWifiClient;
      std::unique_ptr<CloudIoTCoreDevice> mDevice;
      std::unique_ptr<CloudIoTCoreMqtt> mMqtt;
      std::unique_ptr<MQTTClient> mMqttClient;
    };
  } // namespace gcp
}
