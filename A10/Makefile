CC=gcc
SOURCES=marco_polo grep
FILES := $(subst .c,,$(SOURCES))
FLAGS=-g -Wall -Wvla -Werror -Wno-unused-variable -Wno-unused-but-set-variable

# By default, make runs the first target in the file
all: $(FILES)

% :: %.c 
	$(CC) $(FLAGS) $< -o $@ -lpthread -lm

clean:
	rm -rf $(FILES)

