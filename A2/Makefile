#Name: Sophie Zuccolo
#Login: szuccolo
#Student ID: 1293676
#Date: 10/31/25

#Defining variables
CFLAGS = -std=c99 -Wall -pedantic
CC = clang

#Rule to build all files
all: dirs bin/preorder bin/inorder bin/postorder bin/calculate bin/heap

#Rule to make sure the required folders exist
dirs:
	mkdir -p bin obj

#Rules to create the executables
bin/preorder: obj/preorder.o
	$(CC) $(CFLAGS) obj/preorder.o -o bin/preorder

bin/inorder: obj/inorder.o
	$(CC) $(CFLAGS) obj/inorder.o -o bin/inorder

bin/postorder: obj/postorder.o
	$(CC) $(CFLAGS) obj/postorder.o -o bin/postorder

bin/calculate: obj/calculate.o
	$(CC) $(CFLAGS) obj/calculate.o -lm -o bin/calculate

bin/heap: obj/heap.o
	$(CC) $(CFLAGS) obj/heap.o -o bin/heap

#Rules to create the object files
obj/preorder.o: src/preorder.c src/header.h
	$(CC) $(CFLAGS) -c src/preorder.c -o obj/preorder.o

obj/inorder.o: src/inorder.c src/header.h
	$(CC) $(CFLAGS) -c src/inorder.c -o obj/inorder.o

obj/postorder.o: src/postorder.c src/header.h
	$(CC) $(CFLAGS) -c src/postorder.c -o obj/postorder.o

obj/calculate.o: src/calculate.c src/header.h
	$(CC) $(CFLAGS) -c src/calculate.c -o obj/calculate.o

obj/heap.o: src/heap.c src/header.h
	$(CC) $(CFLAGS) -c src/heap.c -o obj/heap.o

#Rules for cleaning up files
clean:
	rm -f obj/*.o

cleaner:
	rm -f obj/*.o bin/preorder bin/inorder bin/postorder bin/calculate bin/heap
