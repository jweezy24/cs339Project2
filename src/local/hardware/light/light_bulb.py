import socket
import sys
import os
import time
sys.path.insert(0, './hardware')
import controlCenter
import struct
import binascii

class Bulb:
    def __init__(self, name, color="default", dim=0, power=True):
        self.server = ('<broadcast>', 8000)
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        self.port = None
        self.name = name
        self.type = "bulb"
        self.power = power
        self.color = color.lower()
        self.dim = dim
        self.grouped = False
        self.heart = Heart(body=self, socket=self.socket)

    def send_boot(self):
        self.socket.sendto('{'\
        'op: boot,'           \
        'type: bulb,'         \
        '{s}'                 \
        '}'.format(s=self.j_summary), self.server)

    def listen(self):
        while True:
            message = ''
            address = ''
            try:
                message, address = self.server_socket.recvfrom(1024)
            except socket.timeout:
                print("timeout")
                return
            try:
                msg = eval(message)
                print(msg)

                if json_message['op'] == 'creds':
                    print('applying creds from DM.\nname: {}\nport: {}'.format(msg['object']['name'],
                                                                               msg['object']['port']))
                    self.set_name(msg['object']['name'])
                    self.set_port(msg['object']['port'])
                    self.heart.start()


    def j_summary(self):
        return "'object': {" \
            "'port': {po},"  \
            "'type': {tp},"  \
            "'name': {nm},"  \
            "'power': {pw}," \
            "'color': {cl}," \
            "'dim': {dm},"   \
            "'grouped': {gp}"\
        "}".format(po=self.port, tp=self.type,
                   nm=self.name, pw=self.power,
                   cl=self.color, dm=self.dim,
                   gp=self.grouped)

    def set_name(self, name):
        self.name = name

    def set_port(self, port):
        self.port = port

    def get_state(self):
        return self.power

    def flip(self):
        self.power = not self.power

    def set_dim(self, dim):
        self.dim = dim

    def get_dim(self):
        return self.dim

    def set_color(self, color):
        self.color = color

    def get_color(self):
        return self.color
