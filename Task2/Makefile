CFLAGS = -Wall -Wextra -O2

RELEASEFILES = src/Main.c src/Output.c src/Sorter.c src/StructureCreator.c
DEBUGFILES   = src/RunTests.c src/Output.c src/Sorter.c src/StructureCreator.c src/Tests.c
HEADERFILES  = src/Output.h src/Sorter.h src/StructureCreator.h 
DEBUGHEADERFILES = src/Output.h src/Sorter.h src/StructureCreator.h src/Tests.h

all: $(RELEASEFILES) $(HEADERFILES) textfiles/hamlet.txt
	gcc $(CFLAGS) -o HamletSorter  $(RELEASEFILES)

debug: $(DEBUGFILES) $(DEBUGHEADERFILES)
	gcc $(CFLAGS) -DDEBUG -o HamletSorterDebug $(DEBUGFILES)

clean:
	rm HamletSorter HamletSorterDebug textfiles/rhymed_hamlet.txt textfiles/sorted_hamlet.txt textfiles/source_hamlet.txt textfiles/text.txt

