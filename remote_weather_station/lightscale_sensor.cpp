#include "lightscale_sensor.hpp"

#include <Arduino.h>

namespace sensor
{
  namespace analog
  {
    LightscaleSensor::LightscaleSensor(const int pin, const std::string name):
      Sensor(pin, name)
    {
    }

    float LightscaleSensor::readValue()
    {
      return analogRead(mPin);
    }
  } // namespace analog
} // namespace sensor
