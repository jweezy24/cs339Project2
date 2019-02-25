import socket
import sys
import json
import time
import threading

class deviceManager:
    def __init__(self):
        #self.server_address = 'localhost'
        self.connection = None
        self.objects = []
        self.threads = []
        self.threads_front = []
    def init_network(self):
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
        self.front_end_socket.bind(('0.0.0.0', 7999))
    def listen(self):
        message = ''
        address = ''
        try:
            message, address = self.server_socket.recvfrom(1024)
            if str(message) == "b'aye'":
                self.server_socket.sendto("what up boo".encode(), address)
                return
        except socket.timeout:
            print("timeout")
            return
        self.parse_json(message)

    def parse_json(self, packet):
        try:
            if(str(packet) == "d'shutdown"):
                return "shutdown"
            json_message = eval(packet)
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

            if json_message['op'] == 'list':
                return self.display_objects()
            if json_message['op'] == 'turn-off':
                self.turn_off(json_message['port'], False)
            if json_message["op"] == 'turn-on':
                self.turn_on(json_message['port'], False)
            if json_message["op"] == 'sched':
                self.sched_event(json_message)
        except NameError:
            print('Incorrect Json format')
    #Jack
    #TODO Test
    def name_check(self, port):
        for i in self.objects:
            if i[0] == port:
                return True
        return False
    #multicast function
    def clapBack(self,port,ip):
        #self.client_socket.sendto("robot".encode(), (ip, int(port)))
        self.multicast_socket.sendto("robot".encode(), (self.MCAST_GRP, self.MCAST_PORT))
    #Asbel
    #TODO Test
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

    def turn_off(self, port, debug):
        for i in self.objects:
            if(i[0] == port):
                if(i[1]["switch"]):
                    i[1]["switch"] = False
                    if not debug:
                        self.send_out_update(i)
                    return

    def turn_on(self, port, debug):
        for i in self.objects:
            if(i[0] == port):
                if(not i[1]["switch"]):
                    i[1]["switch"] = True
                    if not debug:
                        self.send_out_update(i)
                    return
    #Faisal
    #TODO Test
    def triggerTimer(self, json_message):
        time.sleep(json_message["time"])
        if(json_message["event"] == "on"):
            self.turn_on(json_message["port"], False)
        else:
            self.turn_off(json_message["port"], False)

    def sched_event(self, json_message):
        t = threading.Thread(target=self.triggerTimer, args=(json_message,))
        t.start()

    def send_out_update(self, object):
        t = threading.Thread(target=self.update, args=(object,))
        t.start()

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

    def update(self, object):
        object[1]["op"] = "update"
        self.multicast_socket.sendto(str(object[1]).encode(), (self.MCAST_GRP, self.MCAST_PORT))

    #Asbel
    #TODO Test
    def get_object(self,port):
        for i in self.objects:
            if(ip[0] == port):
                return i
        return None

    def handle_front(self):
        self.front_end_socket.listen(2)
        connection, client_address = self.front_end_socket.accept()
        self.connection = connection
        connection.settimeout(2)
        t = threading.currentThread()
        message=''
        while getattr(t, "do_run", True):
            t = threading.currentThread()
            try:
                try:
                    message = connection.recv(1024)
                except socket.timeout as e:
                    print("TCP timeout")
                    continue
                print(self.objects)

                try:
                    message = self.parse_json(message)
                except SyntaxError as e:
                    connection.close()
                    self.front_end_socket.shutdown(socket.SHUT_RDWR)
                    connection = self.connect_front_end()
                    continue
                if(message == 'shutdown'):
                    connection.close()
                    self.front_end_socket.shutdown(socket.SHUT_RDWR)
                    connection = self.connect_front_end()
                    continue
                if(message != '' and type(message) != type(None)):
                    connection.send(str(message).encode())
            except ValueError as e:
                print(e)
                connection.close()
                self.front_end_socket.shutdown(socket.SHUT_RDWR)
        if(type(connection) != type(None)):
            connection.close()
        return

    def connect_front_end(self):
        t = threading.currentThread()
        if(getattr(t, "do_run", True)):
            self.front_end_socket.listen(2)
            connection, client_address = self.front_end_socket.accept()
            return connection

    #Jack
    #TODO Test
    def display_objects(self):
        retStr = ""
        for i in self.objects:
            retStr += "Port: " + str(i[1]["port"]) + "\tOn: " + str(i[1]["switch"]) + "\n"
        print(retStr)
        return retStr

    def socket_close(self):
        self.server_socket.close()
        self.multicast_socket.close()
        self.client_socket.close()


def main():
    devices = deviceManager()
    devices.init_network()
    devices.init_front()
    while True:
        try:
            devices.listen()
        except KeyboardInterrupt:
            t =threading.currentThread()
            t.do_run = False
            for i in devices.threads_front:
                i.do_run = False

            devices.socket_close()

if __name__ == "__main__":
    main()
