import time
import datetime



def timer(smartDev, commands):
    if commands.get('color') != '':
        smartDev.setColor(commands.get('color'))
    time.sleep(int(commands.get('time'))) # this method from the time lib takes seconds as its arg
    op = commands.get('op')
    if op == 'power-on':
        if not smartDev.switch:
            smartDev.flip()
    elif op == 'power-off':
        if smartDev.switch:
            smartDev.flip()
    elif op == 'color':
        smartDev.setColor(commands.get('color'))
    elif op == 'color-on':
        smartDev.setColor(commands.get('color'))
        if not smartDev.switch:
            smartDev.flip()
    elif op == 'color-off':
        smartDev.setColor(commands.get('color'))
        if smartDev.switch:
            smartDev.flip()
    elif op == 'trigger-event':
        if not smartDev.getState():
            smartDev.flip()
        print 'device ' + smartDev.name + " is " + smartDev.triggerEvent()
    return notify(smartDev)



def scheduleTime(smartDev, commands):
    now = datetime.datetime.now()
    val = now.strftime('%Y-%m-%d %H:%M:%S').split(' ')
    #parses time values into integer list so math operations can be done
    futureTime = parseTime(val[0], val[1], commands)
    diff =  futureTime - now
    op = commands.get('op')
    if op == 'power-on':
        time.sleep(diff.total_seconds())
        if not smartDev.switch:
            smartDev.flip()
    elif op == 'power-off':
        time.sleep(diff.total_seconds())
        if smartDev.switch:
            smartDev.flip()
    elif op == 'color':
        time.sleep(diff.total_seconds())
        smartDev.setColor(commands.get('color'))
    elif op == 'color-on':
        time.sleep(diff.total_seconds())
        smartDev.setColor(commands.get('color'))
        if not smartDev.switch:
            smartDev.flip()
    elif op == 'color-off':
        time.sleep(diff.total_seconds())
        smartDev.setColor(commands.get('color'))
        if smartDev.switch:
            smartDev.flip()
    elif op == 'trigger-event':
        time.sleep(diff.total_seconds())
        if not smartDev.getState():
            smartDev.flip()
        print 'device ' + smartDev.name + " is " + smartDev.triggerEvent()

    notifySched(smartDev)

def notify(dev):
    print "Device " + str(dev.name) + " is now " + str(dev.getState())

def notifySched(dev):
    print "Device " + str(dev.name) + " is now " + str(dev.getState()) + " at the time " + str(datetime.datetime.now())

def parseTime(date, time, newTime):
    timeObject = 'none'
    if 'year' in newTime.keys():
        timeObject = datetime.datetime(int(newTime.get('year')), int(newTime.get('month')),
        int(newTime.get('day')), int(newTime.get('hours')), int(newTime.get('minutes')),
        int(newTime.get('seconds')))
    else:
        parsedDate = date.split('-')
        timeObject = datetime.datetime(int(parsedDate[0]),int(parsedDate[1]),int(parsedDate[2]),
        int(newTime.get('hours')), int(newTime.get('minutes')), int(newTime.get('seconds')))

    return timeObject
