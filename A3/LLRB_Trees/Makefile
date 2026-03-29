INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)

OBJS 		 := customErrorClass.o LLRB.o mainLLRB.o
DEPS 		 := ${INCLUDE_DIRS}/customErrorClass.h

.PHONY: clean all

all: mainLLRB

mainLLRB: $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) mainLLRB

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

mainLLRB.o: mainLLRB.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

LLRB.o: LLRB.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

