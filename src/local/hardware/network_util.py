import socket
import sys
import os
import time
sys.path.insert(0, './hardware')
import controlCenter
import struct
import binascii

class Networker:
	def __init__(self):
		sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		sock2.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

		MCAST_GRP = '224.1.1.1'
		MCAST_PORT = 5007
		IS_ALL_GROUPS = True

		sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
		sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		if IS_ALL_GROUPS:
		    # on this port, receives ALL multicast groups
		    sock.bind(('', MCAST_PORT))
		else:
		    # on this port, listen ONLY to MCAST_GRP
		    sock.bind((MCAST_GRP, MCAST_PORT))
		mreq = struct.pack("4sl", socket.inet_aton(MCAST_GRP), socket.INADDR_ANY)

		sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)


		listener_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		listener_socket.bind(('0.0.0.0', 0))

		sock.settimeout(1)

		local_server = ("<broadcast>", 8000)