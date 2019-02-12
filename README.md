# Cs339Project2

We build a system of objects that listen to each other on multiple networks.

## Getting Started

There are three files to run if the user would like to run everything locally.

1) C Server
    To compile, (be in Cs339Project2/src/server) gcc serverMain.c -o test.exe
    To run, ./test.exe 7999     
    The C server code will be running on a server, this is to test everything locally

2) Python 3 Device Manager
    This will always run locally, this acts a middle man between the c server and a local network.
    To run this, (be in Cs339Project2/src/local) python3 deviceManager.py
    To test locally or over multiple networks, device manager has to be run on each machine.

3) Python 2.7 hardware simulation
    To simulate plugging devices in at the lowest level we developed this python app.
    There is a console application, to run (be in Cs339Project2/src/local) python devicesMain.py
    This will give you commands to create objects that will send signals to a locally running device manager.


## Functionality

  * Three distinct levels of operation. (Device Simulation -> Local network manager -> Main server)

  * Sends Json messages over UDP socket functionality

  * (More will come as we continue building the application)


### Installing

Download the repo. Make sure you have a compiler for Python27 and Python3, you do not need a C compiler. The C code is run on a server. If you want to test the server locally then you would need gcc.

## Running the tests

python unittest.py - Running this command will run 31 tests.

(Create C server tests)

(Create deviceManager tests)


## Built With/Requirements

* [Python27](https://www.python.org/download/releases/2.7/) - The compiler for device simulator

* [Python3](https://www.python.org/downloads/release/python-372/) - The compiler for device manager

    * [Netifaces](https://pypi.org/project/netifaces/) - This package is needed for device manager to grab ip

* [C](http://gcc.gnu.org/install/) - The compiler for C

    * [json-c](https://github.com/json-c/json-c) - dependency for server. Parses json args.


## Authors

* **Jack West** - *Built End Point Communications Within All Levels* - [jweezy24](https://github.com/jweezy24)
* **Drew Mack** - *Built Simulator* - [drew-mack](https://github.com/drew-mack)
* **Faisal Shaheen** - *Back-end C Dev* - [F423](https://github.com/F423)
* **Jack Broncato** - *Back-end C Dev* - [jman11111](https://github.com/jman11111)
* **Asbel Assefa** - *Font-end App Developer* - [asbel](https://github.com/asbel)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.
