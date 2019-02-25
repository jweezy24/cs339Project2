import socket
import sys
import os
import time
sys.path.insert(0, './hardware')
import controlCenter
import struct
import binascii
import network_util
import controlCenter

class Bulb:
    def __init__(self, name, color="default", dim=0, power=True):
        self.cc = controlCenter.controller()
        self.net = network_util.Networker()
        self.name = name
        self.type = "bulb"
        self.power = power
        self.color = color.lower()
        self.dim = dim
        self.grouped = False

    def listen(self):
        message = ""
        heartbeat = {"ip":"", "op":"heartbeat", "port":0, "name": self.name, "switch": True, "dim":0, "color":"default"}
        self.cc.add_light(self.name, 'white', True)
        dict = self.cc.jsonifyOject(localManager.get_object_by_name(self.name), 'add')
        dict.update({"port": self.cc.listener_socket.getsockname()[1]})

        while True:
            try:
                message, address = self.cc.sock.recvfrom(1024)
            except self.cc.socket.timeout, e:
                print 'Expection'
                hexdata = binascii.hexlify(message)
                print e
            if not message:
                print "No packets received"
            else:
                heartbeat = eval(message)
            heartbeat["ip"] = dict.get("ip")
            heartbeat["port"] = dict.get("port")
            heartbeat["op"] = "heartbeat"
            print heartbeat
            self.net.sock2.sendto(str(heartbeat), self.net.local_server)

    def j_summary(self): # unused
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
