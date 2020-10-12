CFLAGS = -Wall -Wextra -std=c11

FILES = src/tests.c src/defines.c src/stack.c src/printtypes.c src/utility.c
HEADERFILES = src/stack.h src/templates.h src/defines.h src/utility.h

debug: $(FILES) $(HEADERFILES)
	gcc $(CFLAGS) -O0 -DDEBUG -g -o UnkillableStackDebug $(FILES)

clean: 
	rm UnkillableStackDebug
