#pragma once

#include "sensor.hpp"

namespace sensor
{
  namespace analog
  {
    class HumuniditySensor final : public Sensor
    {
    public:
      explicit HumuniditySensor(const int pin, const std::string name, const float voltage);
      HumuniditySensor(const HumuniditySensor&) = delete;
      HumuniditySensor& operator=(const HumuniditySensor&) = delete;
      virtual ~HumuniditySensor() = default;

      virtual float readValue() final;

    private:
      const float mVoltage;
    };
  } // namespace analog
} // namespace sensor
