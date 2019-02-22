import socket
import netifaces
import sys
import json
import time
import threading

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
        self.front_end_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.front_end_socket.bind(('', 7999))
        self.front_end_socket.settimeout(2)
        #self.server_address = 'localhost'
        self.objects = []
        self.threads = []
        self.threads_front = []
    def listen(self):
        message = ''
        address = ''
        try:
            message, address = self.server_socket.recvfrom(1024)
        except socket.timeout:
            print("timeout")
            return

        #try:
        json_message = eval(message)
        print(json_message)
        if json_message['op'] == 'heartbeat':
            if(not self.name_check(json_message["port"])):
                print('object added.')
                self.objects.append((json_message["port"],json_message))
                self.init_timeout_obj(json_message["port"])
            else:
                self.reset_timeout(json_message["port"])
        if json_message['op'] == 'delete':
            print('object deleted.')
            self.remove_Item(json_message["object"]["name"])
            print(self.objects)
            self.client_socket.sendto(str(json_message).encode(), (self.server_address, 7999))
    #except NameError:
        #print('Incorrect Json format')
    def getMask(self):
        interfaces = netifaces.interfaces()
        addresses = {}
        for i in interfaces:
            tempDict = netifaces.ifaddresses(i)
            if len(tempDict.keys()) > 0:
                addresses.update({i: (tempDict.get(2)[0]['netmask'], tempDict.get(2)[0]['addr'])})
        return addresses

    def name_check(self, port):
        for i in self.objects:
            if i[0] == port:
                return True
        return False
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

    def init_timeout_obj(self, object_port):
        t = threading.Thread(target=self.timeout, args=(object_port,))
        self.threads.append((t, object_port))
        t.start()

    def init_front(self):
        t = threading.Thread(target=self.handle_front)
        self.threads_front.append(t)
        t.start()

    def reset_timeout(self,port):
        for i in self.threads:
            if(i[1] == port):
                i[0].do_run = True
                return

    def timeout(self,port):
        while True:
            t = threading.currentThread()
            if(getattr(t, "do_run", True)):
                time.sleep(2)
                t.do_run = False
            else:
                time.sleep(2)
                if(not getattr(t, "do_run", True)):
                    self.remove_Item(port)
                    print('removed '+ str(port))
                    return port
        return port

    def handle_front(self):
        while True:
            try:
                self.front_end_socket.listen()
            except socket.timeout:
                print("Front-end timeout")


def main():
    devices = deviceManager()
    devices.init_front()
    while True:
        devices.listen()
main()
