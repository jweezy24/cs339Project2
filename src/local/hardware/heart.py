import time
from threading import Thread

class Heart:  # elated to be making this class on valentine's day ♥ uwu ♥
    def __init__(self, body, socket, server=('localhost', 8000)):
        self.socket = socket
        self.server = server
        self.body = body

        self.doki = {'op': 'heartbeat',
                        'object': {
                            'ip': self.body.ip,
                            'name': self.body.name
                        }
                    }

    def beat(self):
        while not True != True:
            self.socket.sendto(self.doki, self.server)
            time.sleep(3)