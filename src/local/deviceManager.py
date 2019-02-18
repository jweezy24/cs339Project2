import socket
import netifaces
import sys
import json
import time

class deviceManager:
    def __init__(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_socket.bind(('', 8000))
        self.server_socket.settimeout(3)
        self.server_address = '67.163.37.156'
        #self.server_address = 'localhost'
        self.objects = []
    def listen(self):
        message = ''
        address = ''
        try:
            message, address = self.server_socket.recvfrom(1024)
        except socket.timeout:
            print("timeout")
            return

        self.clapBack(address)
        try:
            json_message = eval(message)
            print(json_message)
            #subnet_mask
            #for i in subnet_mask.keys():
            #    if subnet_mask.get(i)[1] == json_message['ip']:
            #        json_message['sub'] = subnet_mask.get(i)[0]
            if json_message['op'] == 'add':
                print('object added.')
                self.objects.append((json_message["object"]["name"],json_message))
                self.client_socket.sendto(str(json_message).encode(), (self.server_address, 7999))
                time.sleep(1)
            if json_message['op'] == 'delete':
                print('object deleted.')
                self.remove_Item(json_message["object"]["name"])
                print(self.objects)
                self.client_socket.sendto(str(json_message).encode(), (self.server_address, 7999))
        except NameError:
            print('Incorrect Json format')
    def getMask(self):
        interfaces = netifaces.interfaces()
        addresses = {}
        for i in interfaces:
            tempDict = netifaces.ifaddresses(i)
            if len(tempDict.keys()) > 0:
                addresses.update({i: (tempDict.get(2)[0]['netmask'], tempDict.get(2)[0]['addr'])})
        return addresses
    def clapBack(self,address):
        self.server_socket.sendto("aye".encode(), address)
    def remove_Item(self,item):
        for i in self.objects:
            if item == i[0]:
                self.objects.remove(i)
    def object_scan(self):
        json_dictionary = {"op" : "routine", "objects" : '', "len" :len(self.objects)}
        tmpList =[]
        for i in self.objects:
            i[1]["op"] = "routine"
            self.client_socket.sendto(json.dumps(i[1]).encode(), (self.server_address, 7999))
            time.sleep(0.3)


def main():
    devices = deviceManager()
    while True:
        devices.listen()
        devices.object_scan()
main()
