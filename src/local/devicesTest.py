import socket
import sys
import os
import time
sys.path.insert(0, './hardware')
import utilsForDevs
import controlCenter
import threading
import errno
import datetime
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
                user = raw_input('Enter a command (turn-off, turn-on, list, sched)')
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
            if user == 'turn-on':
                dict = {"op":"turn-on", "port":0}
                name = raw_input('What is the port of the light?')
                dict["port"] = int(name)
                sock2.sendto(str(dict), host)
            if user == "list":
                request = {"op":"list"}
                sock2.sendto(str(request), host)
                data = sock2.recv(1024)
                print(data)
            if user == "sched":
                request = {"op":"sched", "port": 0, "time":0, "event":""}
                dict = {}
                name = raw_input('What is the port of the light?')
                event = raw_input('What would like like to scheduele? (on, off)')
                user_time = raw_input('What time would you like the event to trigger? (15:00:00 day/month/year)')

                parseVals = user_time.split(' ')
                withOutDate = parseVals[0].split(':')
                dict.update({'hours' : int(withOutDate[0])})
                dict.update({'minutes' : int(withOutDate[1])})
                dict.update({'seconds' : int(withOutDate[2])})
                if len(parseVals) > 1:
                    dateParse = parseVals[1].split('/')
                    dict.update({'day' : int(withOutDate[0])})
                    dict.update({'month' : int(withOutDate[1])})
                    dict.update({'year' : int(withOutDate[2])})
                now = datetime.datetime.now()
                val = now.strftime('%Y-%m-%d %H:%M:%S').split(' ')
                #parses time values into integer list so math operations can be done
                futureTime = utilsForDevs.parseTime(val[0], val[1], dict)
                int_time = futureTime - now
                if(int_time.total_seconds() < 0):
                    print("impossible to time travel my guy, reseting to selection.")
                    pipe_check()
                    continue
                else:
                    request.update({"time": int_time.total_seconds()})
                    request.update({"event": event})
                    request.update({"port": int(name)})
                    sock2.send(str(request))


            pipe_check()


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

def pipe_check():
    for i in range(0,2):
        try:
            sock2.send("".encode())
        except socket.error as e:
            if e[0] == errno.EPIPE:
               print "Detected remote disconnect"
               sock2.close()
               sock2.shutdown(socket.SHUT_RDWR)
               print("Exiting program")
            else:
                print("Socket error Disconnecting")
        except:
            sock2.close()
            sock2.shutdown(socket.SHUT_RDWR)
            print("Exiting due to server being down")

main()
