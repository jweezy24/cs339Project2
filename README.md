# Cs339Project2

We build a system of objects that listen to each other on multiple networks. SERVER ONLY WORKS ON DEBIAN BASED OPERATING SYSTEMS.

## Getting Started

There are three files to run if the user would like to run everything locally.

1) C Server
    To compile, (be in Cs339Project2/src/server) `sudo make install`, then `make`
    To run, `./test.exe 7999`     
    The C server code will be running on a server, this is to test everything locally

    Built By:
      * **Jack West** - [jweezy24](https://github.com/jweezy24)
      * **Jack Broncato** - [jman11111](https://github.com/jman11111)

2) Python 3 Device Manager
    This will always run locally, this acts a middle man between the c server and a local network.
    To run this, (be in Cs339Project2/src/local) `python3 deviceManager.py`
    To test locally or over multiple networks, device manager has to be run on each machine.

    Built By:
      * **Jack West** - [jweezy24](https://github.com/jweezy24)

3) Python 2.7 Hardware Simulation
    To simulate plugging devices in at the lowest level we developed scripts to be run as hardware.
    This is a console application, to run (be in Cs339Project2/src/local) `python pluginObject.py <name of object>`
    This will give you commands to create objects that will send signals to a locally running device manager.

    Built By:
      * **Drew Mack** - [drew-mack](https://github.com/drew-mack)

4) Python 2.7 Front-End
    For the user to send commands to their lights, we developed a front-end communication system to send commands to any light on the user's LAN.
    To build, run the command `python devicesTest.py`

    Built By:
      * **Jack West** - [jweezy24](https://github.com/jweezy24)


## Functionality

  #### C Server ####

  * Three distinct levels of operation. (Device Simulation -> Local network manager -> Main server)

  * Sends Json messages over UDP socket functionality

  * Times out device managers after a period of time.

  * Add devices to device manager

  * Delete individual devices

  * Device manager sends out heartbeats every other second.

  * Server reads the heartbeats as "routine" packets.

  * If the server restarts, it rebuilds itself using routine packets.

  #### Device Manager ####

  * Builds objects from heartbeats from hardware

  * Uses multicast to update objects

  * Uses TCP to connect to a front-end

  * Can schedule tasks at specific times in a new thread

  * Front-end TCP connection lives in a new thread

  * Turn on/off lights based off of assigned port

  * Parses json messages to trigger events and build objects

  * Times out objects after not getting a heartbeat for 2-4 seconds

  #### Front End ####

  * Python console application

  * Issues commands over a TCP connection to device manager

  * Able to issue turn on/off, list, and schedule commands

  * Error catching, can be booted up before or after the DM

  * Closes sockets such that it does not break the DM

  #### Device Simulator ####

  * Creates a instance of a device that sends heartbeats to a local DM

  * Can be changed by json messages sent by DM





## Installing


Local:
Download the repo. Make sure you have a compiler for Python27 and Python3, you do not need a C compiler.

Server:
The server currently only runs on a debian based linux distro. While in the server directory (Cs339Project2/src/server), run `sudo make install`. That will install all the packages need to handle the server. Then `make` to build the server.

## Running the tests

* `python unittest.py` - Running this command will run 31 tests.

* In the cs339Project2/test/server run the commands `sudo make install` then `make` then `./testing.exe`

(Create deviceManager tests)


## Built With/Requirements

* [Python27](https://www.python.org/download/releases/2.7/) - The compiler for device simulator

* [Python3](https://www.python.org/downloads/release/python-372/) - The compiler for device manager

    * [Netifaces](https://pypi.org/project/netifaces/) - This package is needed for device manager to grab ip

* [C](http://gcc.gnu.org/install/) - The compiler for C (All C dependencies will be installed with make file)

    * [json-c](https://github.com/json-c/json-c) - dependency for server. Parses json args.

    * [googleTest](https://github.com/google/googletest) - Dependency for C tests


## Authors

* **Jack West** - *Front-end, Server Dev, and networking Dev* - [jweezy24](https://github.com/jweezy24)
* **Drew Mack** - *Built Simulator* - [drew-mack](https://github.com/drew-mack)
* **Jack Broncato** - *Back-end C Dev* - [jman11111](https://github.com/jman11111)
* **Faisal Shaheen** - *Wrote Tests* - [F423](https://github.com/F423)
* **Asbel Assefa** - *Wrote Tests* - [asbel](https://github.com/asbel)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.
