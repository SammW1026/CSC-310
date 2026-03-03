INCLUDE_DIRS := Includes
CC := g++
CFLAGS := -I$(INCLUDE_DIRS)

OBJS := customErrorClass.o dsw.o main.o
DEPS := ${INCLUDE_DIRS}/customErrorClass.h

.PHONY: clean all

all: main

clean:
	rm -f $(OBJS) main

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

dsw.o: dsw.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

main.o: main.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

main: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)