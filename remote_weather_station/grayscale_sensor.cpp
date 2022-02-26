#include "grayscale_sensor.hpp"

#include <Arduino.h>

namespace sensor
{
  namespace analog
  {
    GrayscaleSensor::GrayscaleSensor(const int pin, const std::string name):
      Sensor(pin, name)
    {
    }

    float GrayscaleSensor::readValue()
    {
      return analogRead(mPin);
    }
  } // namespace analog
} // namespace sensor
