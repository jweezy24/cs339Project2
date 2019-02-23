import socket
import sys
import os
import time
sys.path.insert(0, './hardware')
import controlCenter
#this file will simulate plugging hardware into a socket
#sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#sock.sendto('hello'.encode(), ('67.163.37.156', 7999))

sock2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

local_server = ("<broadcast>", 8000)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
sock.settimeout(2)

def main():
    host = connect_to_server()
    while host[0] == 0:
        print("DM not up")
        time.sleep(4)
        host = connect_to_server()
    sock2.connect(host)
    try:
        while True:
            try:
                user = raw_input('Enter a command (turn-off, turn-on, list)')
            except KeyboardInterrupt:
                sock2.shutdown(socket.SHUT_RDWR)
                sock2.close()
                print("Exiting")
                sys.exit(0)
            if user == 'turn-off':
                dict = {"op":"turn-off", "port":0}
                name = raw_input('What is the port of the light?')
                dict["port"] = int(name)
                sock2.sendto(str(dict), host)
            if user == "list":
                request = {"op":"list"}
                sock2.sendto(str(request), host)
                data = sock2.recv(1024)
                print(data)


    except KeyboardInterrupt:
        print('Exiting')
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)


def connect_to_server():
    try:
        sock.sendto("aye", local_server)
        message, address = sock.recvfrom(1024)
        host = (address[0], 7999)
        sock.close()
        return host
    except socket.error:
        return (0,0)



main()
