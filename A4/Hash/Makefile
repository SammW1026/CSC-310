CC     := g++
CFLAGS := -std=c++17 -O2

OBJS := mainHash.o hash.o AVL/avl.o

.PHONY: all run clean

all: hashTable

hashTable: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

mainHash.o: mainHash.cpp hash.h AVL/avl.h
	$(CC) $(CFLAGS) -c -o $@ $<

hash.o: hash.cpp hash.h AVL/avl.h
	$(CC) $(CFLAGS) -c -o $@ $<

AVL/avl.o: AVL/avl.cpp AVL/avl.h
	$(CC) $(CFLAGS) -c -o $@ $<

run: hashTable
	./hashTable

clean:
	rm -f $(OBJS) hashTable hashTable.exe
