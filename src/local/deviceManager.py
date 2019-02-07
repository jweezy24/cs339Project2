import socket
class deviceManager:
    def __init__(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_socket.bind(('', 8000))
    def listen(self):
        message, address = self.server_socket.recvfrom(1024)
        print('recived ' + str(message) + ' from ' + str(address))


def main():
    devices = deviceManager()
    while True:
        devices.listen()
main()
