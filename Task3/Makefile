CFLAGS = -Wall -Wextra -std=c11

FILES = src/tests.c src/defines.c src/stack.c 
HEADERFILES = src/stack.h src/templates.h src/defines.h

all: $(FILES) $(HEADERFILES)
	gcc $(CFLAGS) -O0 -DDEBUG -g -o UnkillableStack $(FILES)

clean: 
	rm UnkillableStack
