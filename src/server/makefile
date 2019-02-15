
CC = gcc

CFLAGS  = -g

TARGET = serverMain

CFLAGS += $(shell pkg-config --cflags json-c)
LDFLAGS += -ljson-c -lpthread

build: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o test.exe $(TARGET).c $(LDFLAGS)

  clean:
	  $(RM) test.exe
		rm -r json-c

install:
	sudo apt install autoconf automake libtool doxygen pkg-config
	git clone https://github.com/json-c/json-c
	cd json-c && libtoolize
	cd json-c && sh autogen.sh
	cd json-c && ./configure  --enable-threading
	cd json-c && make
	cd json-c && make install
	rm -r json-c
