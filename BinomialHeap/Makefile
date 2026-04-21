CC     := g++
CFLAGS := -std=c++17 -O2

OBJS := main.o BinomialHeap.o customErrorClass.o

.PHONY: all run clean

all: BinomialHeap

BinomialHeap: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.cpp BinomialHeap.h
	$(CC) $(CFLAGS) -c -o $@ $<

BinomialHeap.o: BinomialHeap.cpp BinomialHeap.h customErrorClass.h
	$(CC) $(CFLAGS) -c -o $@ $<

customErrorClass.o: customErrorClass.cpp customErrorClass.h
	$(CC) $(CFLAGS) -c -o $@ $<

run: BinomialHeap
	./BinomialHeap

clean:
	rm -f $(OBJS) BinomialHeap BinomialHeap.exe
