
CC = gcc

CFLAGS  = -g

TARGET = serverMain

CFLAGS += $(shell pkg-config --cflags json-c)
LDFLAGS += $(shell pkg-config --libs json-c)

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test.exe $(TARGET).c

  clean:
	  $(RM) test.exe
