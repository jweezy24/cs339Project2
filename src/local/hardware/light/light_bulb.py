import socket
import heart
import sys
import os

class LightBulb:
    def __init__(self, name, color="default", bright=100, power=True):
        self.id = 1
        self.name = name

        self.color = color.lower()
        self.bright = bright
        self.power = power
        self.type = "light_bulb"
        self.grouped = False


        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server = ('localhost', 8000)



    def flip(self):
        self.power = not self.power

    def set_bright(self, bright):
        self.bright = bright

    def get_bright(self):
        return self.bright

    def get_state(self):
        if self.power:
            return "on"
        else:
            return "off"

    def get_color(self):
        return self.color

    def set_color(self, color):
        self.color = color
