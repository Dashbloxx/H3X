CC = gcc
CFLAGS = -Wall -Wextra -Werror
SOURCES = $(wildcard server/*.c)
OBJECTS = $(SOURCES:.c=.o)
TARGET = h3x

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
