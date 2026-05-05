#---------------------------------------------------------------------
# Makefile for the geneRecords project
#
# Targets:
#     make            -> builds everything (default: all)
#     make all        -> compiles object files and the mainSamples binary
#     make run        -> builds (if needed) and runs ./mainSamples samples.bin
#     make clean      -> removes object files and the mainSamples binary
#---------------------------------------------------------------------

INCLUDE_DIRS := Includes
CC           := g++
CFLAGS       := -I$(INCLUDE_DIRS) -Wall -std=c++11

OBJS         := customErrorClass.o geneBank.o
DEPS         := $(INCLUDE_DIRS)/customErrorClass.h geneBank.h

.PHONY: clean all run

all: $(OBJS) mainSamples

clean:
	rm -f $(OBJS) mainSamples

customErrorClass.o: customErrorClass.cpp $(DEPS)
	$(CC) -c -o $@ $(CFLAGS) $<

geneBank.o: geneBank.cpp $(DEPS)
	$(CC) -c -o $@ $(CFLAGS) $<

mainSamples: $(OBJS) mainSamples.cpp
	$(CC) -o $@ $(CFLAGS) mainSamples.cpp $(OBJS)

run: mainSamples
	./mainSamples samples.bin
