PREFIX ?= /usr/local
SRC = main.c
OBJ = $(SRC:.c=.o)
INC = ext
BIN = main

CXX = g++
CC = gcc
CFLAGS = -Wall -Werror -std=c89
CPPFLAGS = -I $(INC)

$(BIN): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $< $(CFLAGS) $(CPPFLAGS) -c -o $@

debug: CFLAGS += -g
debug: CPPFLAGS += -DDEBUG
debug: $(BIN)

clean:
	rm -f $(BIN) $(OBJ)

install: $(BIN)
	cp -f $(BIN) $(PREFIX)/bin/$(BIN)

uninstall: $(BIN)
	rm -f $(PREFIX)/bin/$(BIN)

.PHONY: debug clean install uninstall

