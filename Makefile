CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iserver/include
LDFLAGS = -pthread
SOURCES = $(wildcard server/*.c)
OBJECTS = $(SOURCES:.c=.o)
TARGET = h3x

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
