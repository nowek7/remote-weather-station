#include "pressure_sensor.hpp"

#include <Arduino.h>

namespace sensor
{
  namespace i2c
  {
    PressureSensor::PressureSensor(const int pin,
                                   const std::string name,
                                   const float altitude,
                                   const Precision precision):
      Sensor(pin, name),
      mSensor(&Wire, mSensor.eSDOVDD),
      mAltitude(altitude),
      mPrecision(mSensor.eNormalPrecision1)
    {
      if (precision == Precision::HIGH_PRECISION)
      {
        mPrecision = mSensor.eUltraLowPrecision;
      }
      else if (precision == Precision::LOW_PRECISION)
      {
        mPrecision = mSensor.eLowPrecision;
      }
      else if (precision == Precision::NORMAL_PRECISION2)
      {
        mPrecision = mSensor.eNormalPrecision2;
      }
      else if (precision == Precision::HIGH_PRECISION)
      {
        mPrecision = mSensor.eHighPrecision;
      }
      else if (precision == Precision::ULTRA_PRECISION)
      {
        mPrecision = mSensor.eUltraPrecision;
      }

      int result;
      while ((result = mSensor.begin()) != ERR_OK)
      {
        if (ERR_DATA_BUS == result)
        {
          Serial.println("Data bus error!");
        }
        else if (ERR_IC_VERSION == result)
        {
          Serial.println("The chip version does not match!");
        }
        delay(500);
      }

      setPrecision();
      calibrate();
    }

    void PressureSensor::setPrecision()
    {
      Serial.print("Try set sampling mode.");
      while(!mSensor.setSamplingMode(mPrecision))
      {
        Serial.print(".");
        delay(500);
      }
      Serial.println();
    }

    void PressureSensor::calibrate()
    {
      if (mSensor.calibratedAbsoluteDifference(mAltitude))
      {
        Serial.println("Absolute difference base value set successfully!");
      }
    }

    float PressureSensor::readValue()
    {
      return mSensor.readPressPa();
    }
  }
} // namespace sensor
