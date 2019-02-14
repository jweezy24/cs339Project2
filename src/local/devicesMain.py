import socket
import sys
import os
sys.path.insert(0, './hardware')
import controlCenter
#this file will simulate plugging hardware into a socket
#sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#sock.sendto('hello'.encode(), ('67.163.37.156', 7999))

sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
local_server = ('localhost', 8000)
sock2.sendto('hello'.encode(), local_server)


def main():
    # localManager = controlCenter.controller()
    try:
        while True:
            user = raw_input('Enter a command (add-light move delete)')
            if user == 'add-light':
                # name = raw_input('What is the name of the light?')
                # localManager.add_light(name, 'red', True)
                message = str(localManager.jsonifyOject(localManager.get_object_by_name(name), 'add'))
                sock2.sendto(message, local_server)

    except KeyboardInterrupt:
        print('Exiting')
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)
main()
