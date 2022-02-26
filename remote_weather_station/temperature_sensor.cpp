#include "temperature_sensor.hpp"

#include <Arduino.h>

namespace sensor
{
  namespace analog
  {
    TemperatureSensor::TemperatureSensor(const int pin, const std::string name, const float voltage):
      sensor::Sensor(pin, name),
      mVoltage(voltage)
    {
      Serial.println("TemperatureSensor");
    }

    float TemperatureSensor::readValue()
    {
      const float analogVolt = static_cast<float>(analogRead(mPin) / ADC_RESOLUTION * mVoltage);

      // Convert voltage to celsius degree.
      return -66.875 + 72.917 * analogVolt;
    }
  } // namespace analog
} // namespace sensor
