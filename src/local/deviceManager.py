import socket
import netifaces

class deviceManager:
    def __init__(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_socket.bind(('', 8000))
        self.objects = []
    def listen(self):
        message, address = self.server_socket.recvfrom(1024)
        try:
            json_message = eval(message)
            subnet_mask = self.getMask()
            for i in subnet_mask.keys():
                print(subnet_mask.get(i)[1])
                print(json_message['ip'])
                if subnet_mask.get(i)[1] == json_message['ip']:
                    json_message['sub'] = subnet_mask.get(i)[0]
            if json_message['op'] == 'add':
                print('object added.')
                self.objects.append(json_message)
                self.client_socket.sendto(str(json_message).encode(), ('localhost', 7999))
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


def main():
    devices = deviceManager()
    while True:
        devices.listen()
main()
