import socket
sys.path.insert(0, './hardware')

class Bulb:
    def __init__(self, name, color="default", dim=0, power=True):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.ip =
        self.type = "bulb"
        self.name = name
        self.power = power
        self.color = color.lower()
        self.dim = dim
        self.grouped = False

        self.heart = Heart(body=self, socket=self.socket, )

    def j_summary(self):
        return "'object': {" \
            "'ip': {ip},"    \
            "'type': {tp},"  \
            "'name': {nm},"  \
            "'power': {pw}," \
            "'color': {cl}," \
            "'dim': {dm},"   \
            "'grouped': {gp}"\
        "}".format(ip=self.ip, tp=self.type,
                   nm=self.name, pw=self.power,
                   cl=self.color, dm=self.dim,
                   gp=self.grouped)

    def get_state(self):
        return self.power

    def flip(self):
        self.power = not self.power

    def set_dim(self, dim):
        self.dim = dim

    def get_dim(self):
        return self.dim

    def set_color(self, color):
        self.color = color

    def get_color(self):
        return self.color
