#pragma once

#include "sensor.hpp"

namespace sensor
{
  namespace analog
  {
    class TemperatureSensor final : public Sensor
    {
    public:
      /**
       * @brief Construct a new Temperature Sensor instance
       *
       * @param pin int
       * @param name std::string
       * @param voltage float
       */
      explicit TemperatureSensor(const int pin, const std::string name, const float voltage);
      TemperatureSensor(const TemperatureSensor&) = delete;
      TemperatureSensor& operator=(const TemperatureSensor&) = delete;
      virtual ~TemperatureSensor() = default;

      /**
       * @brief Read temperature from sensor. Unit[°C]
       *
       * @return float
       */
      virtual float readValue() final;

    private:
      const float mVoltage;
    };
  } // namespace analog
} // namespace sensor
