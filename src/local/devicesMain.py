import socket
import sys
import os
from hardware import *
#this file will simulate plugging hardware into a socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto('hello'.encode(), ('67.163.37.156', 7999))

sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto('hello'.encode(), ('localhost', 8000))


def main():
    try:
        while True:
            user = input('Enter a command (add move delete)')
            if user == 'add':
                pass

    except KeyboardInterrupt:
        print('Exiting')
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)
