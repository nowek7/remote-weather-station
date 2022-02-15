from machine import Pin

class Sensor:
    def __init__(self, name, pin_number, mode=-1):
        self.__name = name
        self.__pin = Pin(pin_number, mode)

    def __repr__(self):
        print(f"Sensor: {self.__name} | Pin: {self.__pin}")

    @property
    def name(self):
        return self.__name

    @property
    def pin(self):
        return self.__pin

class TemperatureSensor(Sensor):
    pass

class HumiditySensor(Sensor):
    pass

class PressureSensor(Sensor):
    pass

class LightScaleSensor(Sensor):
    pass

class GrayScaleSensor(Sensor):
    pass