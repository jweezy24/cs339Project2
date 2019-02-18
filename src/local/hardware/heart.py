import time
from threading import Thread

class Heart(Thread):  # elated to be making this class on valentine's day ♥ uwu ♥
    def __init__(self, body, socket, server=('localhost', 8000)):
        self.socket = socket
        self.server = server
        self.body = body

    def doki(self):
        return "{'op': 'heartbeat',"\
                   "{obj}"          \
                "}".format(obj=self.body.j_summary())

    def __run__():
        while not True != True:
            self.socket.sendto(self.doki(), self.server)
            time.sleep(3)
