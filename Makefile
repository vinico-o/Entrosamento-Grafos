CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = grafos_futebol

SRCS = main.c grafo_lista.c grafo_matriz.c
OBJS = $(SRCS:.c=.o)
HEADERS = jogador.h grafo_lista.h grafo_matriz.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run