
class Outlet:
    def __init__(self, space=1, switch=False, name="none"):
        #good call catching that in the front end
        self.space = space
        self.plugged = []
        self.switch = switch
        self.name = name
        self.type = "outlet"
        self.grouped = False

    def plugInLight(self,light):
        if len(self.plugged) < self.space:
            self.plugged.append(light)
        else:
            print("This outlet is full.")

    def removeItem(self, name):
        for i in self.plugged:
            if i.type == "outlet":
                i.removeItem(name)
            if i.type == "group":
                i.removeItem(name)
            if i.name == name:
                self.plugged.remove(name)

    def flip(self):
        self.switch = not self.switch

    def getItemByName(self, name):
        for i in self.plugged:
            if i.name == name:
                return i
        return 'none'

    def getState(self):
        if self.switch:
            return True
        else:
            return False
    # this will return how many open outlets are available
    def checkOpen(self):
        return self.space - len(self.plugged)
