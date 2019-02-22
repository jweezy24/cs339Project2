import socket
import sys
import os
import time
sys.path.insert(0, './hardware')
import controlCenter
import struct
import binascii

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

local_server = ("localhost", 8000)
localManager = controlCenter.controller()

def main():
    message2 = ""
    heartbeat = {"ip":"", "op":"heartbeat", "port":0 }
    localManager.add_light(sys.argv[1], 'red', True)
    dict = localManager.jsonifyOject(localManager.get_object_by_name(sys.argv[1]), 'add')
    dict.update({"port": listener_socket.getsockname()[1] })
    message = str(dict)
    sock2.sendto(message, local_server)

    while True:
        try:
            message2, address = sock.recvfrom(1024)
        except socket.error, e:
            print 'Expection'
            hexdata = binascii.hexlify(message2)
            print 'Data = %s' % hexdata
        if not message2:
            print "No packets received"
        else:
            print message2
            heartbeat["ip"] = dict.get("ip")
            heartbeat["port"] = dict.get("port")
        sock2.sendto(str(heartbeat), local_server)

main()
