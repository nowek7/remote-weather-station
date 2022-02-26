#pragma once

#include <string>

namespace sensor
{
  constexpr int ADC_RESOLUTION = 1024;
  constexpr float VOLTAGE_5 = 5.0;
  constexpr float VOLTAGE_3_3 = 3.3;

  class Sensor
  {
  public:
    /**
     * @brief Construct a new Sensor instance
     *
     * @param pin int
     * @param name std::string
     */
    explicit Sensor(const int pin, const std::string name);
    Sensor(const Sensor&) = delete;
    Sensor& operator=(const Sensor&) = delete;
    virtual ~Sensor() = default;

    /**
     * @brief Get the number of a connection pin.
     *
     * @return int
     */
    int getPin() const;

    /**
     * @brief Get sensor name
     *
     * @return std::string
     */
    std::string getName() const;

    /**
     * @brief Read value from sensor
     *
     * @return float
     */
    virtual float readValue() = 0;

  protected:
    int mPin;
    std::string mName;
  };
} // namespace sensor
