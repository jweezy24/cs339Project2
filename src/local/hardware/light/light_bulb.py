
class Bulb:
    def __init__(self, name, color="default", dim=0, power=True):
        self.color = color.lower()
        self.dim = dim
        self.power = power
        self.name = name
        self.type = "bulb"
        self.grouped = False

    def j_summary(self):
        return "'object': {"
            "'ip': {ip},"
            "'name': {nm}"
        }"

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
