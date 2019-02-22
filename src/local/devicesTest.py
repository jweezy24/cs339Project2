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

def main():
    host = connect_to_server()
    while host[0] == 0:
        print("server not up")
        time.sleep(4)
        host = connect_to_server()
    sock2.connect(host)
    try:
        while True:
            user = raw_input('Enter a command (turn-off, turn-on, list)')
            if user == 'turn-off':
                dict = {"op":"turn-off", "name":""}
                name = raw_input('What is the name of the light?')
                dict["name"] = name
                sock2.sendto(str(dict), address)
            if user == "list":
                request = {"op":"list"}


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
