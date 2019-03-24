all: gofish.x

gofish.x: main.o deck.o card.o
	gcc -std=c99 main.o deck.o card.o -o gofish.x
	
card.o: card.c card.h
	gcc -std=c99 -c card.c
	
deck.o: deck.c deck.h card.c card.h
	gcc -std=c99 -c deck.c

main.o: main.c deck.c deck.h card.c card.h
	gcc -std=c99 -c main.c
	
clean:
	rm *.o *.x