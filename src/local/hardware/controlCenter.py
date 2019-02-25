import threading
import utilsForDevs
import light_bulb
import outletObject
import lightGroup
import miscObject
import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

class controller:
    def __init__(self):
        self.threads = []
        self.fixtures = []

    def setTimer(self, object, commands):
        t = threading.Thread(target=utilsForDevs.timer, args=(self.get_object_by_name(object),commands, ))
        t.daemon = True
        t.start()

    def setSchedule(self, object, commands):
        t = threading.Thread(target=utilsForDevs.scheduleTime, args=(self.get_object_by_name(object),commands, ))
        t.daemon = True
        t.start()

    def move_item(self, name, destination):
        oldDestination = ''
        foundDest = False
        if destination == name:
            print('The item your trying to move is itself. Returning home.')
            return
        item = ''
        for i in self.fixtures:
            if i.type == 'group' or i.type == 'outlet':
                if i.type == 'group' and i.getItemByName(name) != "none":
                    item = i.getItemByName(name)
                    oldDestination = i
                if i.type == 'outlet' and i.getItemByName(name) != "none":
                    item = i.getItemByName(name)
                    oldDestination = i
                if i.name == destination and i.type == 'group':
                    foundDest = True
                    destination = i
        if oldDestination != '' and oldDestination.type == 'group':
            oldDestination.removeItem(item.name)
        if foundDest:
            destination.addItem(item)
            return True
        return False

    def add_object(self, name, outlet_capability, type, event, switch):
        self.fixtures.append(miscObject.newSmartDev(name, type, event, outlet_capability, switch))

    def add_group(self,name, members, switch):
        self.fixtures.append(lightGroup.lightGroup(name=name, objects=members, switch=switch))

    def add_light(self, light):
        self.fixtures.append(light)

    def add_outlet(self,space, switch, name):
        if space > 7:
            print('That is too many spaces. No outlet created.')
            return
        self.fixtures.append(outletObject.Outlet(space=space, switch=switch, name=name))

    def gather_group(self):
        options = list()
        devices = list()
        print('What devices belong to this group? Options are as follows:')
        for f in self.fixtures:
            if not f.grouped and f.type != 'group':
                options.append(f.name)
                devices.append(f)
                print(f.name)
        print('When you are done adding members, type "done".')

        member_names = list()
        members = list()
        while 1:
            proposed_member = raw_input('> ')
            if proposed_member == 'done' and len(members) >= 2:
                break
            elif proposed_member == 'done' and len(members) < 2:
                print('You may not make a group with less than 2 members.')
                continue
            if proposed_member not in options:
                print('"{}" is not a groupable fixture, please try again.'.format(proposed_member))
                continue
            if proposed_member in member_names:
                print('"{}" has already been added to this group.'.format(proposed_member))
                continue
            members.append(devices[options.index(proposed_member)])
            member_names.append(proposed_member)
            self.delete(proposed_member)
            print('added "{}" to the group.'.format(proposed_member))

        return tuple(members)

    def show_fixtures(self): # 3 for loops instead of 1 because we want same-type objects to show up together
        output=[]
        #print 'These are the current outlets:'
        for f in self.fixtures:
            if f.type == 'outlet':
                if f.switch:
                    state = 'on'
                else:
                    state = 'off'
                output.append('Name: {0}\t Type: {1}\t State: {2}'.format(f.name, f.type, state))
                output.append(self.get_full_outlet_object(f))

            elif f.type == 'group':
                if f.switch:
                    state = 'on'
                else:
                    state = 'off'
                header = 'Name: {0}\t Type: {1}\t State: {2}'.format(f.name, f.type, state)
                for i in self.get_full_group_object(f):
                    header = header + "\n" + i
                output.append(header)
        #print 'These are the current lights:'
            else:
                if f.switch:
                    state = 'on'
                else:
                    state = 'off'
                output.append('Name: {0}\t Type: {1}\t State: {2}'.format(f.name, f.type, state))
        return output


    def get_full_outlet_object(self, outlet):
        outlets = []
        for i in outlet.plugged:
            if i.type == 'group':
                outlets.append(self.get_full_group_object(i))
            elif i.type == 'outlet':
                outlets.appned(self.get_full_outlet_object(i))
            else:
                if i.switch:
                    state = 'on'
                else:
                    state = 'off'
                outlets.append('\tName: {0}\t Type: {1}\t State: {2}'.format(i.name, i.type, state))
        return outlets

    def get_full_group_object(self,group):
        groups = []
        for i in group.group:
            if i.type == 'group':
                groups.append(self.get_full_group_object(i))
            elif i.type == 'outlet':
                groups.appned(self.get_full_outlet_object(i))
            else:
                if i.switch:
                    state = 'on'
                else:
                    state = 'off'
                groups.append('\tName: {0}\t Type: {1}\t State: {2}'.format(i.name, i.type, state))
        return groups

    def update_light(self, name, dim='', state='', color=''):
        light = self.get_object_by_name(name)
        if dim != '':
            light.setDim(dim)
        if state != '':
            if state:
                if not light.switch:
                    light.flip()
            if not state:
                if light.switch:
                    light.flip()
        if color != '':
            light.setColor(color)


    def update_outlet(self, light, on=False):
        if light != 'none':
            if (self.get_object_by_name(name) != 'none' and self.get_object_by_name(name).type != 'group'
            or self.get_object_by_name(name).type != 'group'):
                object.plugInLight(self.get_object_by_name(name))
                return
        if not on:
            if object.switch:
                object.flip()
                return
        if on:
            if not object.switch:
                object.flip()
                return

    def update_group(self, name, op=False):
        object = self.get_object_by_name(name)
        if op:
            if not object.switch:
                object.flip()
        if not op:
            if object.switch:
                object.flip()

    def get_object_by_name(self, name):
        for i in self.fixtures:
            if i.name == name:
                return i
            if i.type == 'group' or i.type == 'outlet':
                if i.getItemByName(name) != 'none':
                    return i.getItemByName(name)
        return 'none'

    def delete(self,name):
        for i in self.fixtures:
            if i.type != 'group' and i.name == name:
                self.fixtures.remove(i)
            else:
                if i.type == 'group':
                    if i.getItemByName(name) != 'none':
                        i.removeItem(name)

    #Fasal
    #TODO Test
    def jsonifyOject(self, thing, op):
        try:
            s.connect(("8.8.8.8", 80))
            if thing.type == 'bulb':
                jsonDict = { 'op': op, 'ip': str(s.getsockname()[0]), 'sub':'', 'object':{'type': thing.type, 'color' : thing.color,
                'state': str(thing.switch), 'dim' : thing.dim, 'name': thing.name} }
                return jsonDict
        except:
            if thing.type == 'bulb':
                jsonDict = { 'op': op, 'ip': '127.0.0.1', 'sub':'', 'object':{'type': thing.type, 'color' : thing.color,
                'state': str(thing.switch), 'dim' : thing.dim, 'name': thing.name} }
                return jsonDict
