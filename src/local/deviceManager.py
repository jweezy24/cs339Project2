import socket
import netifaces
import sys
import json
import time

class deviceManager:
    def __init__(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.multicast_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        self.MULTICAST_TTL = 32
        self.multicast_socket.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, self.MULTICAST_TTL)
        self.server_socket.bind(('', 8000))
        self.MCAST_GRP = '224.0.0.1'
        self.MCAST_PORT = 5007
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

        try:
            json_message = eval(message)
            print(json_message)
            #subnet_mask
            #for i in subnet_mask.keys():
            #    if subnet_mask.get(i)[1] == json_message['ip']:
            #        json_message['sub'] = subnet_mask.get(i)[0]
            if json_message['op'] == 'add':
                print('object added.')
                self.objects.append((json_message["port"],json_message))
                #self.client_socket.sendto(str(json_message).encode(), (self.server_address, 7999))
                self.clapBack(json_message["port"], json_message["ip"])
                time.sleep(3)
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
    #multicast function
    def clapBack(self,port,ip):
        #self.client_socket.sendto("robot".encode(), (ip, int(port)))
        self.multicast_socket.sendto("robot".encode(), (self.MCAST_GRP, self.MCAST_PORT))
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
