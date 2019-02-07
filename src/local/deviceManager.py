import socket
class deviceManager:
    def __init__(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_socket.bind(('', 8000))
        self.objects = []
    def listen(self):
        message, address = self.server_socket.recvfrom(1024)
        try:
            json_message = eval(message)
            if json_message['op'] == 'add':
                print('object added.')
                self.objects.append(json_message)
        except NameError:
            print('Incorrect Json format')


def main():
    devices = deviceManager()
    while True:
        devices.listen()
main()
