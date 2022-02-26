#pragma once

#include "sensor.hpp"

namespace sensor
{
  namespace analog
  {
    // 1 Lux to 6000 Lux
    enum class LIGHT_SCALE: uint16_t
    {
      MOONLIGHT = 50,
      SUNRISE = 500,
      OVERCAST_DAYLIGHT = 2000,
      AMBIENT_DAYLIGHT = 3500,
      DIRECT_SUNLIGHT = 5000
    };

    class LightscaleSensor final : public Sensor
    {
    public:
      /**
       * @brief Construct a new Lightscale Sensor instance
       *
       * @param pin int
       * @param name std::string
       */
      explicit LightscaleSensor(const int pin, const std::string name);
      LightscaleSensor(const LightscaleSensor&) = delete;
      LightscaleSensor& operator=(const LightscaleSensor&) = delete;
      ~LightscaleSensor() = default;

      /**
       * @brief Read lightscale level from sensor
       *
       * @return float
       */
      virtual float readValue() final;
    };
  } // namespace analog
} // namespace sensor
