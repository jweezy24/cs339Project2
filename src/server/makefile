
CC = gcc

CFLAGS  = -g

TARGET = serverMain

CFLAGS += $(shell pkg-config --cflags json-c)
LDFLAGS += $(shell pkg-config --libs json-c) -lpthread

build: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -Wall -o test.exe $(TARGET).c  $(LDFLAGS)

  clean:
	  $(RM) test.exe
		rm -r json-c

install:
	sudo apt install autoconf automake libtool doxygen pkg-config
	git clone https://github.com/json-c/json-c
	cd json-c && libtoolize
	cd json-c && sh autogen.sh
	cd json-c && ./configure
	cd json-c && make
	cd json-c && make install
	sudo ldconfig /usr/local/lib
	rm -r json-c
