#include "provider.hpp"

#include <sstream>
#include <Arduino.h>

namespace network
{
  void init(const WiFiMode_t mode)
  {
    WiFi.mode(mode);
    if (WiFi.isConnected())
    {
      WiFi.disconnect();
    }
  }

  bool connect(const std::string& ssid, const std::string& password)
  {
    if (WiFi.isConnected())
    {
      WiFi.disconnect();
    }

    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.print("Try to connect to WIFI...");
    while ((WiFi.status() != WL_CONNECTED))
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("Device is connnected to WIFI!");

    // Sanity check
    return (WiFi.status() == WL_CONNECTED) ? true : false;
  }

  void disconnect()
  {
    if (WiFi.isConnected())
    {
      WiFi.disconnect();
    }
  }

  std::vector<network_t> getAvailableNetworks()
  {
    std::vector<network_t> networks;

    const int numNetworks = WiFi.scanNetworks();
    for (int i = 0; i < numNetworks; ++i)
    {
      networks.emplace_back(WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i));
    }
    WiFi.scanDelete();
    return networks;
  }

  void printAvailableNetworks()
  {
    std::stringstream ss;

    // WiFi.scanNetworks will return the number of networks found
    auto networks = getAvailableNetworks();
    ss << "Found number of networks: " << networks.size() << "\n";

    for (std::size_t i = 0; i < networks.size(); ++i)
    {
      ss << "SSID: " << std::get<0>(networks[i]) << " | ";
      ss << std::get<1>(networks[i]) << "|";
      ss << std::get<2>(networks[i]) << "|";
      ss << std::get<3>(networks[i]) << "\n";
    }

    const std::string rawLog = ss.str();
    Serial.println(rawLog.c_str());
  }
}
