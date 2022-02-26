#include "sensor.hpp"

#include <Arduino.h>

namespace sensor
{
  Sensor::Sensor(const int pin, const std::string name):
    mPin(pin),
    mName(mName)
  {
    Serial.println("Sensor");
  }

  int Sensor::getPin() const
  {
    return mPin;
  }

  std::string Sensor::getName() const
  {
    return mName;
  }
} // namespace sensor
