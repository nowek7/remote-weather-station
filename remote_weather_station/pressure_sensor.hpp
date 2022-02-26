#pragma once

#include "sensor.hpp"

#include <DFRobot_BMP3XX.h>

namespace sensor
{
  namespace i2c
  {
    /**
      ULTRA_LOW_PRECISION: suitable for weather monitoring (minimum power consumption), power mode is enforcing mode

      LOW_PRECISION: suitable for random detection, power mode is normal mode

      NORMAL_PRECISION1: suitable for dynamic detection on handheld devices (such as mobile phones),
                         power mode is normal mode

      NORMAL_PRECISION2: suitable for drones, power mode is normal mode

      HIGH_PRECISION: suitable for low-power handheld devices (such as mobile phones), power mode is normal mode

      ULTRA_PRECISION: suitable for indoor guide, the collection rate is very low and the collection period is 1000ms,
                       power mode is normal mode
    */
    enum class Precision
    {
      ULTRA_LOW_PRECISION,
      LOW_PRECISION,
      NORMAL_PRECISION1,
      NORMAL_PRECISION2,
      HIGH_PRECISION,
      ULTRA_PRECISION
    };

    class PressureSensor : public Sensor
    {
    public:
      /**
       * @brief Construct a new Pressure Sensor instance
       *
       * @param pin int
       * @param name std::string
       * @param altitude float
       * @param precision Precision enum class
       */
      explicit PressureSensor(const int pin,
                              const std::string name,
                              const float altitude,
                              const Precision precision);
      PressureSensor(const PressureSensor&) = delete;
      PressureSensor& operator=(const PressureSensor&) = delete;
      ~PressureSensor() = default;

      /**
       * @brief Read pressure from sensor. Unit [Pa]
       *
       * @return float
       */
      float readPressure();

      virtual float readValue() final;

    private:
      DFRobot_BMP388_I2C mSensor;
      const float mAltitude;
      DFRobot_BMP388_I2C::ePrecisionMode_t mPrecision;

      /**
       * @brief Calibrate sensor
       */
      void calibrate();

      /**
       * @brief Set precision of sensor
       */
      void setPrecision();
    };
  } // namespace i2c
} // namespace sensor
