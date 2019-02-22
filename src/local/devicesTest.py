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


def main():
    local_server = ('127.0.0.1', 7999)
    sock2.connect(local_server)
    localManager = controlCenter.controller()
    try:
        while True:
            user = raw_input('Enter a command (turn-off, turn-on, list)')
            if user == 'turn-off':
                name = raw_input('What is the name of the light?')
                localManager.add_light(name, 'red', True)
                message = str(localManager.jsonifyOject(localManager.get_object_by_name(name), 'add'))
                sock2.sendto(message, local_server)
            if user == "list":
                request = {"op":"list"}


    except KeyboardInterrupt:
        print('Exiting')
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)



main()
