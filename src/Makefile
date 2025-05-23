CC = gcc
CFLAGS = -Wall -g

SRCS = main.c tablero.c piezas.c movimientos.c juego.c
OBJS = $(SRCS:.c=.o)
TARGET = ajedrez

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)