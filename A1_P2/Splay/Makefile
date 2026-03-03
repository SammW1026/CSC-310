INCLUDE_DIRS := Includes
CC := g++
CFLAGS := -I$(INCLUDE_DIRS)

OBJS := customErrorClass.o splay.o mainsplay.o
DEPS := ${INCLUDE_DIRS}/customErrorClass.h

.PHONY: clean all

all: mainsplay

clean:
	rm -f $(OBJS) mainsplay

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

splay.o: splay.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

mainsplay.o: mainsplay.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

mainsplay: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)