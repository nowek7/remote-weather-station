#include "provider.hpp"

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

    int noTries = 5;
    WiFi.begin(ssid.c_str(), password.c_str());
    while ((WiFi.status() != WL_CONNECTED) && (noTries != 0))
    {
      delay(500);
      Serial.print("Connecting...");
      noTries--;
    }

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
}
