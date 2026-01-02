#Name: Sophie Zuccolo
#Login: szuccolo
#Student ID: 1293676
#Date: 09/26/25

#Defining variables
CFLAGS = -std=c99 -Wall -pedantic -fPIC -I./src
CC = clang

#Rule to build all files
all: dirs obj/array.o obj/list.o obj/mem.o lib/libarray.so lib/liblist.so lib/libmem.so

#Rule to make sure the required folders exist
dirs:
	mkdir -p bin obj lib

#Rules to create the object files
obj/array.o: src/array.c src/array.h
	$(CC) $(CFLAGS) -c src/array.c -o obj/array.o

obj/list.o: src/list.c src/list.h
	$(CC) $(CFLAGS) -c src/list.c -o obj/list.o

obj/mem.o: src/mem.c src/mem.h
	$(CC) $(CFLAGS) -c src/mem.c -o obj/mem.o

#Rules to create the shared libraries
lib/libmem.so: obj/mem.o
	$(CC) -shared -fPIC obj/mem.o -o lib/libmem.so

lib/libarray.so: obj/array.o lib/libmem.so
	$(CC) -shared -fPIC obj/array.o -Llib -lmem -o lib/libarray.so

lib/liblist.so: obj/list.o lib/libmem.so
	$(CC) -shared -fPIC obj/list.o -Llib -lmem -o lib/liblist.so

#Rules for cleaning up files
clean:
	rm -f obj/*.o

cleaner:
	rm -f obj/*.o lib/*.so bin/*
