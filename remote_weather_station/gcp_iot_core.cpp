#include "gcp_iot_core.hpp"

#include "config.hpp"

namespace network
{
  namespace gcp
  {
    constexpr int KEEP_ALIVE = 180;
    constexpr bool HAS_CLEAN_SESSION = true;
    constexpr int MQTT_TIMEOUT = std::chrono::seconds(1).count();

    IoTClient::IoTClient(const Config& config):
      mWifiClient(nullptr),
      mDevice(nullptr),
      mMqtt(nullptr),
      mMqttClient(nullptr)
    {
      mWifiClient = std::unique_ptr<WiFiClientSecure>(new WiFiClientSecure());
      mDevice = std::unique_ptr<CloudIoTCoreDevice>(
        new CloudIoTCoreDevice(config.projectId.c_str(),
                               config.cloudRegion.c_str(),
                               config.registryId.c_str(),
                               config.deviceId.c_str(),
                               PRIVATE_KEY));
      mMqttClient = std::unique_ptr<MQTTClient>(new MQTTClient(512));
      mMqtt = std::unique_ptr<CloudIoTCoreMqtt>(new CloudIoTCoreMqtt(mMqttClient.get(), mWifiClient.get(), mDevice.get()));

      mWifiClient->setCACert(ROOT_CERT);
      mMqttClient->setOptions(KEEP_ALIVE, HAS_CLEAN_SESSION, MQTT_TIMEOUT);

      mMqtt->setUseLts(true);
      mMqtt->startMQTT();
      mMqtt->loop();
    }

    IoTClient::~IoTClient()
    {
      mMqttClient->disconnect();
    }

    void IoTClient::connect()
    {
      mMqtt->mqttConnect();
    }

    bool IoTClient::publish(const std::string& data)
    {
      return mMqtt->publishTelemetry(data.c_str());
    }
  } // namespace gcp
} // namespace network
