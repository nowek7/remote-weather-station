#pragma once

#include <vector>
#include <tuple>

#include <ESP8266WiFi.h>

namespace network
{
  typedef std::tuple<std::string, int, int, unsigned char> network_t;

  /**
   * @brief Set WiFi to station mode and disconnect from an AP.
   *
   * @param mode Flag
   */
  void init(const WiFiMode_t mode);

  /**
   * @brief Connect to access point
   *
   * @param ssid     Wifi ssid
   * @param password Wifi password
   * @return bool
   */
  bool connect(const std::string& ssid, const std::string& password);

  /**
   * @brief Disconnect from access point
   *
   */
  void disconnect();

  /**
   * @brief Get available networks
   *
   * @return std::vector<network_t>
   */
  std::vector<network_t> getAvailableNetworks();
} // network
