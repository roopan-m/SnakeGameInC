ARGS = -std=c11 -Wall -ggdb3


eat : main.o array.o game.o random.o terminal.o newSleep.o LinkedList.o
	gcc main.o array.o game.o random.o terminal.o newSleep.o LinkedList.o -o eat $(ARGS)

LinkedList.o: LinkedList.c List.h
	gcc -c LinkedList.c List.h $(ARGS)

main.o : main.c array.h
	gcc -c main.c $(ARGS)

array.o: array.h array.c
	gcc -c array.c $(ARGS)

game.o : game.h game.c
	gcc -c game.c $(ARGS)

random.o : random.h random.c
	gcc -c random.c $(ARGS)

terminal.o : terminal.h terminal.c
	gcc -c terminal.c $(ARGS)

newSleep.o : newSleep.c newSleep.h
	gcc -c newSleep.c $(ARGS)


clean : 
	rm -f main.o array.o game.o random.o terminal.o newSleep.o LinkedList.o eat