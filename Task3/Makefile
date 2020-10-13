CFLAGS = -Wall -Wextra -std=c11

DEBUG_FLAGS = -DSTACK_CHECK -DSTACK_CANARY -DSTACK_HASH

FILES = src/tests.c src/defines.c src/stack.c src/printtypes.c src/utility.c
HEADERFILES = src/stack.h src/templates.h src/defines.h src/utility.h

light: $(FILES) $(HEADERFILES)
	gcc $(CFLAGS) -O2 -DNDEBUG -o UnkillableStackLight $(FILES)

hard: $(FILES) $(HEADERFILES)
	gcc $(CFLAGS) -O0 $(DEBUG_FLAGS) -g -o UnkillableStackHard $(FILES)

clean: 
	rm UnkillableStackLight UnkillableStackHard
