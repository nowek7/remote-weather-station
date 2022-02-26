#include "humunidity_sensor.hpp"

#include <Arduino.h>

namespace sensor
{
  namespace analog
  {
    HumuniditySensor::HumuniditySensor(const int pin, const std::string name, const float voltage):
      Sensor(pin, name),
      mVoltage(voltage)
    {
    }

    float HumuniditySensor::readValue()
    {
      const float analogVolt = static_cast<float>(analogRead(mPin) / ADC_RESOLUTION * mVoltage);

      // Convert voltage to relative humidity (%)
      return -12.5 + 41.667 * analogVolt;
    }
  } // namespace analog
} // namespace sensor
