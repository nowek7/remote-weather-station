import util
import esp

import machine
import network
import network.mqtt_client as MqttClient
import ntptime
import utime

def connect_network(config):
    network_provider = network.WLAN(network.STA_IF)
    network_provider.active(True)

    if not network_provider.isconnected():
        network_provider.connect(config.network['ssid'], config.network['password'])
        while not network_provider.isconnected():
            pass

    print(f'network config: {network_provider.ifconfig()}')

    return network_provider

def set_machine_time():
    ntptime.settime()
    tm = utime.localtime()
    tm = tm[0:3] + (0,) + tm[3:6] + (0,)
    machine.RTC().datetime(tm)

    print(f'Current time: {utime.localtime()}')

def run():
    config = util.get_config()
    set_machine_time()

    topics = {
        '/temperature': 1,
        '/pressure': 1,
        '/humidity': 1,
        '/grayscale': 1,
        '/lightscale': 1
    }

    while True:
        network = connect_network(config)

        mqtt = MqttClient(config)
        mqtt.register_calback(lambda topic, message: print((topic, message)))
        mqtt.connect()

        mqtt.subscribe(topics)

        # TODO: Gather data from sensors.
        # TODO: Send data to cloud.

        network.disconnect()
        mqtt.disconnect()
        utime.sleep(60 * 60)


if __name__ == '__main__':
    esp.osdebug(0)
    run()