import threading
import utilsForDevs
import light_bulb
import outletObject


class lightGroup:
    def __init__(self, name, switch, objects=()):  # parentheses in the def here makes it a tuple instead of a list
        self.name = name                                    # better because lists are mutable, can cause goofiness when mutable object type in argument def
        self.group = []
        self.switch = switch
        self.threads = []
        self.type = "group"
        self.grouped = False
        for i in objects:
            self.addElement(i)

    def __len__(self):
        return len(self.group)

    def addElement(self, light):
        self.group.append(light)


    def getState(self):
        values = []
        if self.switch:
            values.append((self.name, "on"))
        else:
            values.append((self.name, "off"))
        for i in self.group:
            if i.type == "outlet":
                if i.switch:
                    print(str(i.name) + " is powered on.")
                    values.append((i.name, "on"))
                    for j in i.plugged:
                        if j.switch:
                            print(str(j.name) + " is turned on.")
                        else:
                            print(str(j.name) + "is turned off.")
                else:
                    print(str(i.name) + " is powered off.")
                    values.append((i.name, "off"))
                    for j in i.plugged:
                        print(str(j.name) + "is powered off.")
                        values.append((i.name, ))
            if i.type == "bulb":
                if i.switch:
                    print(str(i.name) + " is powered on.")
                    values.append((i.name, "on"))
                else:
                    print(str(i.name) + " is powered off.")
                    values.append((i.name, "off"))
            if i.type == "group":
                values.append(i.getState())
        return values
    def flip(self):
        self.switch = not self.switch

    def getItemByName(self, name):
        for i in self.group:
            if i.type == "outlet":
                for j in i.plugged:
                    if j.name == name:
                        return j
            if name == i.name:
                return i
            if i.type == "group":
                return i.getItemByName(name)
        return "none"

    def getItemByIndex(self, index):
        for i in range(0 , len(self.group)):
            if i == index:
                return i
        return "none"

    def addLight(self, name, color, outlet="none", switch=False):
        light = lightObject.Bulb(name, color, switch)
        if outlet is not "none":
            for i in self.group:
                if i.name == outlet:
                    i.plugInLight(light)
                    return
        else:
            self.group.append(light)

    def addOutlet(self, name, space=1, state=False):
        self.group.append(outletObject.Outlet(name,space,state))

    def addItem(self, item):
        self.group.append(item)

    def removeItem(self, name):
        for i in self.group:
            if i.type == "outlet":
                i.removeItem(name)
            if i.type == "group":
                i.removeItem(name)
            if i.name == name:
                self.group.remove(i)
