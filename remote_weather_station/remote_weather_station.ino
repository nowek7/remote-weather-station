#include "config.hpp"
#include "gcp_config.hpp"
#include "humunidity_sensor.hpp"
#include "gcp_iot_core.hpp"
#include "grayscale_sensor.hpp"
#include "lightscale_sensor.hpp"
#include "pressure_sensor.hpp"
#include "provider.hpp"
#include "temperature_sensor.hpp"

#include <time.h>
#include <ArduinoJson.h>

namespace analog_sensor = sensor::analog;
namespace i2c_sensor = sensor::i2c;

namespace
{
  constexpr int TIME_VALUE = 1510644967;
  constexpr int SHORT_TIMEOUT = 10;
  constexpr int HOUR_IN_SECONDS = std::chrono::seconds(60 * 60).count();

  // The size was computed from https://arduinojson.org/v6/assistant/
  constexpr int PAYLOAD_SIZE = 192;
} // namespace

void timeSync()
{
  configTime(HOUR_IN_SECONDS, 0, NTP_PRIMARY, NTP_SECONDARY);
  while (time(nullptr) < TIME_VALUE)
  {
    delay(SHORT_TIMEOUT);
  }
}

void setup()
{
  Serial.begin(115200);

  network::init(WIFI_STA);

  Serial.println("Setup done");
}

void loop()
{
  Serial.println("Start");

  // Read config.
  DynamicJsonDocument config(CONFIG_SIZE);
  DeserializationError error = deserializeJson(config, CONFIG_FILE);
  if (error != DeserializationError::Ok)
  {
    Serial.print("Failed to deserialize config - ");
    Serial.println(error.f_str());
    return;
  }

  // Setup wifi connection.
  const auto ssid = config["network"]["ssid"].as<const char*>();
  const auto password = config["network"]["password"].as<const char*>();
  const auto connected = network::connect(ssid, password);
  if (!connected)
  {-
    Serial.println("Not connected to internet!");
    return;
  }

  // Setting up the time on the device.
  timeSync();

  // Connect to google cloud platform.
  network::gcp::Config gcpConfig =
  {
    .projectId = config["gcp"]["project_id"].as<const char*>(),
    .cloudRegion = config["gcp"]["cloud_region"].as<const char*>(),
    .registryId = config["gcp"]["registry_id"].as<const char*>(),
    .deviceId = config["gcp"]["device_id"].as<const char*>(),
    .mqttBridgeHostname = config["gcp"]["mqtt_bridge_hostname"].as<const char*>(),
    .mqttBridgePort = config["gcp"]["mqtt_bridge_port"].as<int>()
  };
  network::gcp::IoTClient iotClient(gcpConfig);
  iotClient.connect();

  // Create payload.
  DynamicJsonDocument json(PAYLOAD_SIZE);

  // Analog sensors.
  {
    {
      analog_sensor::TemperatureSensor temperatureSHT30(A0,
                                                        "Gravity: Analog SHT30 Temperature Sensor",
                                                        sensor::VOLTAGE_5);
      json["temperature"] = temperatureSHT30.readValue();
    }
    {
      analog_sensor::HumuniditySensor humuniditySHT30(A1,
                                                      "Gravity: Analog SHT30 Humidity Sensor",
                                                      sensor::VOLTAGE_5);
      json["humunidity"] = humuniditySHT30.readValue();
    }
    {
      analog_sensor::GrayscaleSensor grayscale(A2, "Gravity: Analog Grayscale Sensor");
      json["grayscale"] = grayscale.readValue();
    }
    {
      analog_sensor::LightscaleSensor lighscale(A3, "Gravity: Analog Lighscale Sensor");
      json["lighscale"] = lighscale.readValue();
    }

    // I2C sensor.
    {
      i2c_sensor::PressureSensor pressureBMP388(-1,
                                                "Gravity: BMP388 Barometric Pressure Sensors",
                                                3.0,
                                                i2c_sensor::Precision::ULTRA_LOW_PRECISION);
      json["pressure"] = pressureBMP388.readValue();
    }
  }

  // Generate the minified JSON and send it to the Serial port.
  std::string payload;
  const auto writtenBytes = serializeJson(json, payload);
  iotClient.publish(payload);

  network::disconnect();

  // Wait a bit before scanning again
  delay(HOUR_IN_SECONDS * 1000);
}
