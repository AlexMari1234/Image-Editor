# Copyright 2020 Darius Neatu <neatudarius@gmail.com>

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=image_editor

build:$(TARGETS)

image_editor: *.c
	$(CC) $(CFLAGS) *.c -o image_editor -lm

pack:
	zip -FSr 312CA_AlexandruMarinescu_Tema3.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean

