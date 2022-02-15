from common import util

from umqtt.simple import MQTTClient

class MqttClient:
    def __init__(self, config):
        jwt = util.create_jwt(config.gcp['project_id'],
                              config.token['private_key'],
                              config.token['algorithm'],
                              config.token['token_ttl'])

        self.__client_id = self.__gcp_id(config.gcp)
        self.__client = MQTTClient(self.__client_id.encode('utf-8'),
                                   server = config.gcp['mqtt_bridge_hostname'],
                                   port = config.gcp['mqtt_bridge_port'],
                                   user = b'ignored',
                                   password = jwt.encode('utf-8'),
                                   ssl = True)

    def __del__(self):
        pass

    def __gcp_id(config):
        return f'projects/{config["project_id"]}/locations/{config["cloud_region"]}/registries/{config["registry_id"]}/devices/{config["device_id"]}'

    def connect(self):
        self.__client.connect()

    def disconnect(self):
        self.__client.disconnect()

    def register_cb(self, callback):
        self.__client.set_callback(callback)

    def subcribe(self, topic, qos = 1):
        self.__client.subscribe(topic, qos)

    def subcribe(self, topics):
        for topic, qos in topics.items():
            self.__client.subscribe(topic, qos)

    def publish(self, topic, message, retain = False, qos = 0):
        self.__client.publish(topic, message, retain, qos)
        self.__client.wait_msg()