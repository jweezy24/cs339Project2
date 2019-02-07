
class newSmartDev:
    def __init__(self, name, type, event, outlet_capability, switch):
        self.name = name
        self.type = type
        self.event = event
        self.outlet_capability = outlet_capability
        self.switch = switch
        self.grouped = False

    def triggerEvent(self):
        return self.event

    def flip(self):
        self.switch = not self.switch

    def can_be_plugged(self):
        return self.outlet_capability

    def getState(self):
        return self.switch

    def getEvent(self):
        return self.event
