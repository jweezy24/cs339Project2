class Bulb:
    # I was thinking we treat the dim setting as a percentage
    # 0 is no dim 100 is fully dimmed
    # the switch setting will tell us if the light is on or off
    # if switch is false the light is off, if the switch is true the light is on
    # Color will be a string value that will define the color
    # Outlet is the smart outlet the light is tied to
    def __init__(self, name, color="default", dim=0, switch=True):
        self.color = color.lower()
        self.dim = dim
        self.switch = switch
        self.name = name
        self.type = "bulb"
        self.grouped = False

    def flip(self):
        self.switch = not self.switch

    def setDim(self, dim):
        self.dim = dim

    def getDim(self):
        return self.dim

    def getState(self):
        if self.switch:
            return "Light is on"
        else:
            return "Light is off"

    def getColor(self):
        return self.color

    def setDim(self, val):
        self.dim = val

    def setColor(self, color):
        self.color = color
    def getColor(self):
        return self.color
