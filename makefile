OBJS	= main.o wordlib.o stack.o list.o context.o shell.o
SOURCE	= main.c wordlib.c stack.c list.c context.c shell.c
HEADER	= stack.h list.h context.h util.h wordlib.h shell.h
OUT	= sixteenth
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

wordlib.o: wordlib.c
	$(CC) $(FLAGS) wordlib.c 

stack.o: stack.c
	$(CC) $(FLAGS) stack.c 

list.o: list.c
	$(CC) $(FLAGS) list.c 

context.o: context.c
	$(CC) $(FLAGS) context.c 

shell.o: shell.c
	$(CC) $(FLAGS) shell.c 


clean:
	rm -f $(OBJS) $(OUT)
