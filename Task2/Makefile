CFLAGS = -Wall -Wextra 

RELEASEFILES = src/Main.c src/Output.c src/Sorter.c src/StructureCreator.c
DEBUGFILES   = src/RunTests.c src/Output.c src/Sorter.c src/StructureCreator.c src/Tests.c
HEADERFILES  = src/Output.h src/Sorter.h src/StructureCreator.h 
DEBUGHEADERFILES = src/Output.h src/Sorter.h src/StructureCreator.h src/Tests.h

all: $(RELEASEFILES) $(HEADERFILES) textfiles/hamlet.txt
	gcc $(CFLAGS) -O2 -o HamletSorter  $(RELEASEFILES)

debug: $(DEBUGFILES) $(DEBUGHEADERFILES)
	gcc $(CFLAGS) -O0 -DDEBUG -g -o HamletSorterDebug $(DEBUGFILES)

clean:
	rm HamletSorter HamletSorterDebug textfiles/rhymed_hamlet.txt textfiles/sorted_hamlet.txt textfiles/source_hamlet.txt textfiles/text.txt

