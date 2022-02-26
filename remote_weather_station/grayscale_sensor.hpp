#pragma once

#include "sensor.hpp"

namespace sensor
{
  namespace analog
  {
    class GrayscaleSensor final : public Sensor
    {
    public:
      /**
       * @brief Construct a new Grayscale Sensor instance
       *
       * @param pin int
       * @param name std::string
       */
      explicit GrayscaleSensor(const int pin, const std::string name);
      GrayscaleSensor(const GrayscaleSensor&) = delete;
      GrayscaleSensor& operator=(const GrayscaleSensor&) = delete;
      ~GrayscaleSensor() = default;

      /**
       * @brief Read grayscale level from sensor
       *
       * @return float
       */
      virtual float readValue() final;
    };
  } // namespace analog
} // namespace sensor
