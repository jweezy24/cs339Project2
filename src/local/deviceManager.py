import socket
import netifaces
import sys

class deviceManager:
    def __init__(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_socket.bind(('', 8000))
        self.server_address = '67.163.37.156'
        self.objects = []
    def listen(self):
        message, address = self.server_socket.recvfrom(1024)
        self.clapBack(address)
        try:
            json_message = eval(message)
            subnet_mask = self.getMask()
            for i in subnet_mask.keys():
                if subnet_mask.get(i)[1] == json_message['ip']:
                    json_message['sub'] = subnet_mask.get(i)[0]
            if json_message['op'] == 'add':
                print('object added.')
                self.objects.append(json_message)
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


def main():
    devices = deviceManager()
    while True:
        devices.listen()
main()
