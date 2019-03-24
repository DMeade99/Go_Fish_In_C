#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "card.h"
#include "deck.h"

struct deck
{
	Card head;
	Card tail;
	int size;
};

Deck createEmptyDeck()
{
	Deck newDeck = malloc(sizeof(*newDeck));
	newDeck->head = NULL;
	newDeck->tail = NULL;
	newDeck->size = 0;

	return newDeck;
}

Deck createFullDeck()
{
	Deck newDeck = malloc(sizeof(*newDeck));
	newDeck->head = NULL;
	newDeck->tail = NULL;
	newDeck->size = 0;

	int a, b;
	for (a = 0; a < 13; a++)
	{
		for (b = 0; b < 4; b++)
		{
			append(newDeck, a, b);
		}

	}

	shuffleDeck(newDeck, 4);

	return newDeck;
}

void append(Deck currentDeck, int Rank, int Suit)
{
	Card newCard = createCard(Rank, Suit, NULL);
	currentDeck->size += 1;

	if (currentDeck->tail == NULL)
	{
		currentDeck->head = newCard;
		currentDeck->tail = newCard;
		return;
	}

	setNextCard(currentDeck->tail, newCard);
	currentDeck->tail = newCard;
}

void prepend(Deck currentDeck, int Rank, int Suit)
{
	Card newCard = createCard(Rank, Suit, NULL);

	if (currentDeck->tail == NULL)
	{
		currentDeck->tail = newCard;
	}

	setNextCard(newCard, currentDeck->head);
	currentDeck->head = newCard;
	currentDeck->size += 1;
}

void removeAt(Deck currentDeck, int position)
{
	if ((currentDeck->size < 0) || (position < 0) || (position > (currentDeck->size)))
	{
		printf("\nUnable to remove card at position %d.\n", position);
		exit(1);
	}

	currentDeck->size -= 1;
	if (position == 0)
	{
		Card tempCard = currentDeck->head;
		currentDeck->head = getNextCard(currentDeck->head);
		printf("\n%s %s removed\n", getRank(tempCard), getSuit(tempCard));
		freeCard(tempCard);

		if (position == currentDeck->size)
		{
			currentDeck->tail = NULL;
		}
	}
	else
	{

		Card currentCard = currentDeck->head;
		int currentPosition = 0;

		while (currentPosition < (position - 1))
		{
			currentPosition++;
			currentCard = getNextCard(currentCard);
		}

		Card tempCard = getNextCard(currentCard);
		setNextCard(currentCard, getNextCard(tempCard));
		printf("\n%s %s removed\n", getRank(tempCard), getSuit(tempCard));
		freeCard(tempCard);

		if (position == currentDeck->size)
		{
			currentDeck->tail = NULL;
		}
	}
}

int getLength(Deck currentDeck)
{
	return currentDeck->size;
}

void printDeck(Deck currentDeck)
{
	Card currentCard = currentDeck->head;
	Card nextCard = getNextCard(currentCard);

	while (currentCard != NULL)
	{
		if (nextCard == NULL)
		{
			printf("%s %s\n", getRank(currentCard), getSuit(currentCard));
			break;
		}
		else
		{
			printf("%s %s", getRank(currentCard), getSuit(currentCard));

			if (strcmp(getRank(currentCard), getRank(nextCard)) == 0)
			{
				printf(", %s %s", getRank(nextCard), getSuit(nextCard));

				if (getNextCard(nextCard) != NULL)
				{
					currentCard = nextCard;
					nextCard = getNextCard(nextCard);
				}
			}
		}

		printf("\n");

		currentCard = nextCard;
		nextCard = getNextCard(nextCard);
	}

}

void shuffleDeck(Deck currentDeck, int times)
{
	Deck shuffledDeck = malloc(sizeof(*shuffledDeck));

	int a;
	for (a = 0; a < times; a++)
	{
		shuffledDeck->head = currentDeck->head;
		shuffledDeck->tail = currentDeck->head;

		Card slow_ptr, fast_ptr;

		slow_ptr = currentDeck->head;
		fast_ptr = getNextCard(currentDeck->head);

		while (fast_ptr != NULL)
		{
			fast_ptr = getNextCard(fast_ptr);

			if (fast_ptr != NULL)
			{
				slow_ptr = getNextCard(slow_ptr);
				fast_ptr = getNextCard(fast_ptr);
			}
		}

		currentDeck->head = getNextCard(currentDeck->head);
		Card split = getNextCard(slow_ptr);

		setNextCard(shuffledDeck->tail, split);
		shuffledDeck->tail = getNextCard(shuffledDeck->tail);
		split = getNextCard(split);


		while (split != NULL)
		{
			setNextCard(shuffledDeck->tail, currentDeck->head);
			shuffledDeck->tail = getNextCard(shuffledDeck->tail);
			currentDeck->head = getNextCard(currentDeck->head);

			setNextCard(shuffledDeck->tail, split);
			shuffledDeck->tail = getNextCard(shuffledDeck->tail);
			split = getNextCard(split);
		}

		currentDeck->head = shuffledDeck->head;
	}
}

void mergeDeck(Deck currentDeck)
{
	merge(&currentDeck->head);
}

void merge(Card *head)
{
	Card temp = *head;
	Card front;
	Card back;

	if ((temp == NULL) || (getNextCard(temp) == NULL))
	{
		return;
	}

	// Partition list into halves
	partitionDeck(temp, &front, &back);

	merge(&front);
	merge(&back);

	// Merge the sorted lists together
	*head = sortDeckRank(front, back);

}

void partitionDeck(Card temp, Card *front, Card *back)
{
	Card fast_ptr, slow_ptr;

	// Check for length of less than 2 nodes
	if ((temp == NULL) || (getNextCard(temp) == NULL))
	{
		*front = temp;
		*back = NULL;
	}
	else
	{
		slow_ptr = temp;
		fast_ptr = getNextCard(temp);

		while (fast_ptr != NULL)
		{
			fast_ptr = getNextCard(fast_ptr);

			if (fast_ptr != NULL)
			{
				slow_ptr = getNextCard(slow_ptr);
				fast_ptr = getNextCard(fast_ptr);
			}
		}


		*front = temp;
		*back = getNextCard(slow_ptr);
		setNextCard(slow_ptr, NULL);
	}

}

Card sortDeckRank(Card front, Card back)
{
	Card result;

	if (front == NULL)
	{
		return back;
	}
	else if (back == NULL)
	{
		return front;
	}

	if (getNumRank(front) <= getNumRank(back))
	{
		result = front;
		setNextCard(result, sortDeckRank(getNextCard(front), back));
	}
	else
	{
		result = back;
		setNextCard(result, sortDeckRank(front, getNextCard(back)));
	}


	return result;
}

Card sortDeckSuit(Card front, Card back)
{
	Card result;

	if (front == NULL)
	{
		return back;
	}
	else if (back == NULL)
	{
		return front;
	}

	if (getNumSuit(front) <= getNumSuit(back))
	{
		result = front;
		setNextCard(result, sortDeckSuit(getNextCard(front), back));
	}
	else
	{
		result = back;
		setNextCard(result, sortDeckSuit(front, getNextCard(back)));
	}

	return result;
}

void insertIntoHand(Deck hand, Card newCard)
{
	prepend(hand, getNumRank(newCard), getNumSuit(newCard));
}

void dealCards(Deck fullDeck, Deck hand, int numOfCards)
{
	int currentPosition = 1;
	hand->head = fullDeck->head;
	hand->size = 0;
	Card currentCard = fullDeck->head;

	while (currentPosition < numOfCards)
	{
		currentCard = getNextCard(currentCard);
		currentPosition++;
		hand->size++;
	}

	hand->tail = currentCard;
	fullDeck->head = getNextCard(currentCard);
	setNextCard(currentCard, NULL);

	mergeDeck(hand);
}

Card drawCard(Deck fullDeck)
{	
	Card newCard = fullDeck->head;

	fullDeck->head = getNextCard(fullDeck->head);

	return newCard;
}

Card getRandom(Deck currentDeck)
{
	srand(time(NULL));
	int increment = (rand() % currentDeck->size);
	Card randomCard = currentDeck->head;
	int a;
	for (a = 0; a < increment; a++)
	{
		randomCard = getNextCard(randomCard);
	}

	return randomCard;
}

void makePlayerGuess(Deck playerHand, Deck computerHand, Deck fullDeck)
{
	char guess[64];
	Card currentCard = computerHand->head;
	int position = 0;
	bool isMatch = 0;

	printDeck(playerHand);
	
	printf("\nPlease select a card from your hand to guess.\n");
	printf("Guesses must be typed in text format (ace, four, nine)\n");
	scanf("%s", guess);

	while (position <= getLength(computerHand))
	{
		if (position == 0)
		{
			if (strcmp(guess, getRank(currentCard)) == 0)
			{
				insertIntoHand(playerHand, currentCard);
				currentCard = getNextCard(currentCard);
				removeAt(computerHand, 0);
				isMatch = 1;
			}
			else
			{
				currentCard = getNextCard(currentCard);
				position++;
			}
		}
		else
		{
			if (strcmp(guess, getRank(currentCard)) == 0)
			{
				insertIntoHand(playerHand, currentCard);
				currentCard = getNextCard(currentCard);
				removeAt(computerHand, position);
				isMatch = 1;
			}
			else
			{
				currentCard = getNextCard(currentCard);
				position++;
			}
		}
	}

	if (isMatch == 1)
	{
		printf("\nNice guess!\n");
		mergeDeck(playerHand);
		printf("You get to guess again.\n");
		makePlayerGuess(playerHand, computerHand, fullDeck);
	}
	else
	{
		printf("\nGo Fish!\n");

		if (isEmpty(fullDeck) == 0)
		{
			insertIntoHand(playerHand, drawCard(fullDeck));
			mergeDeck(playerHand);
		}
		else
		{
			printf("\nThere are no more cards to draw!\n");
		}
	}

}

void makeComputerGuess(Deck computerHand, Deck playerHand, Deck fullDeck)
{
	char guess[64];
	Card currentCard = playerHand->head;
	int position = 0;
	bool isMatch = 0;

	strcpy(guess, getRank(getRandom(computerHand)));

	printf("\nYour opponent has guessed: %s\n\n", guess);

	while (position <= getLength(playerHand))
	{
		if (position == 0)
		{
			if (strcmp(guess, getRank(currentCard)) == 0)
			{
				insertIntoHand(computerHand, currentCard);
				currentCard = getNextCard(currentCard);
				removeAt(playerHand, 0);
				isMatch = 1;
			}
			else
			{
				currentCard = getNextCard(currentCard);
				position++;
			}
		}
		else
		{
			if (strcmp(guess, getRank(currentCard)) == 0)
			{
				insertIntoHand(computerHand, currentCard);
				currentCard = getNextCard(currentCard);
				removeAt(playerHand, position);
				isMatch = 1;
			}
			else
			{
				currentCard = getNextCard(currentCard);
				position++;
			}
		}
	}

	if (isMatch == 1)
	{
		mergeDeck(computerHand);
		makeComputerGuess(computerHand, playerHand, fullDeck);
	}
	else
	{
		printf("\nGo Fish!\n");
		
		if (isEmpty(fullDeck) == 0)
		{
			insertIntoHand(computerHand, drawCard(fullDeck));
			mergeDeck(computerHand);
		}
	}


}

void checkEmpty(Deck currentHand, Deck fullDeck)
{
	if (getLength(currentHand) <= 0)
	{
		if (getLength(fullDeck) < 7)
		{
			dealCards(fullDeck, currentHand, (getLength(fullDeck) + 1));
		}
		else
		{
			dealCards(fullDeck, currentHand, 7);
		}
	}
}

void getBooks(Deck currentHand, Deck bookDeck)
{
	int rankCount[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	Card currentCard = currentHand->head;
	int removeValue = -1;

	while (currentCard != NULL)
	{
		rankCount[getNumRank(currentCard)] += 1;
		currentCard = getNextCard(currentCard);
	}

	// PRINT TO TEST
	int a;
	//for (a = 0; a < 13; a++)
	//{
	//	printf("%d\n", rankCount[a]);
	//}

	for (a = 0; a < 13; a++)
	{
		if (rankCount[a] == 4)
		{
			removeValue = a;
			Card currentCard = currentHand->head;
			int position = 0;

			while (currentCard != NULL)
			{
				if (getNumRank(currentCard) == a)
				{
					insertIntoHand(bookDeck, currentCard);
					currentCard = getNextCard(currentCard);
					removeAt(currentHand, position);
				}
				else
				{
					currentCard = getNextCard(currentCard);
					position++;
				}
			}
		}
	}

}

bool gameOver(Deck playerHand, Deck computerHand, Deck fullDeck)
{
	bool gameStatus = 0;

	if ((isEmpty(playerHand) == 1) && (isEmpty(fullDeck) == 1))
	{
		gameStatus = 1;
	}
	else if ((isEmpty(computerHand) == 1) && (isEmpty(fullDeck) == 1))
	{
		gameStatus = 1;
	}
	else
	{
		gameStatus = 0;
	}

	return gameStatus;
}

bool isEmpty(Deck currentDeck)
{
	bool isEmpty = 0;

	if (currentDeck->head == NULL)
	{
		isEmpty = 1;
	}

	return isEmpty;
}

void freeDeck(Deck currentDeck)
{
	Card currentCard = currentDeck->head;

	while (currentCard != NULL)
	{
		Card nextCard = getNextCard(currentCard);
		free(currentCard);
		currentCard = nextCard;
	}

	free(currentDeck);
}
