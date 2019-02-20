
CC = g++

CFLAGS  = -g

TARGET = serverTests

CFLAGS += $(shell pkg-config --cflags json-c)
LDFLAGS += $(shell pkg-config --libs json-c) -lpthread -lgtest

build: $(TARGET)

$(TARGET): $(TARGET).cc
	$(CC) $(CFLAGS) -o testing.exe $(TARGET).cc  $(LDFLAGS)

  clean:
	  $(RM) testing.exe

install:
	sudo apt-get install cmake g++
	wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz
	tar xf release-1.8.0.tar.gz
	cd googletest-release-1.8.0 && cmake -DBUILD_SHARED_LIBS=ON
	cd googletest-release-1.8.0 && sudo make
	cd googletest-release-1.8.0 && sudo make install
	cd googletest-release-1.8.0 && sudo cp -a googletest/include/gtest /usr/include
	sudo ldconfig /usr/local/lib
	rm release-1.8.0.tar.gz
	sudo rm -r googletest-release-1.8.0
