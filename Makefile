CC = g++-11
CFLAGS = -std=c++-11 -Werror -Wall -g

all: main.exe

main.exe: main.o linked_list.o list.o stack.o queue.o
	$(CC) $(CFLAGS) -o main.exe main.o linked_list.o list.o stack.o queue.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

linked_list.o: linked_list.cpp linked_list.h
	$(CC) $(CFLAGS) -c linked_list.cpp

list.o: list.cpp list.h
	$(CC) $(CFLAGS) -c list.cpp

stack.o: stack.cpp stack.h
	$(CC) $(CFLAGS) -c stack.cpp

queue.o: queue.cpp queue.h
	$(CC) $(CFLAGS) -c queue.cpp

clean:
	rm -f *.o main.exe
