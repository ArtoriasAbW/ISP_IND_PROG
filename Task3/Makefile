CFLAGS = -Wall -Wextra -std=c11 -O2 -o

FILES = src/tests.c src/defines.c src/stack.c 
HEADERFILES = src/stack.h src/templates.h src/defines.h

all: $(FILES) $(HEADERFILES)
	gcc $(CFLAGS) UnkillableStack $(FILES)

clean: 
	rm UnkillableStack
