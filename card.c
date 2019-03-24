#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "card.h"

struct card
{
	int Suit;
	int Rank;
	Card next;
};

Card createCard(int Rank, int Suit, Card next)
{
	Card newCard = malloc(sizeof(*newCard));
	newCard->Suit = Suit;
	newCard->Rank = Rank;
	newCard->next = next;

	return newCard;
}

char* getSuit(Card currentCard)
{
	char* suit[] = { "hearts", "spades", "clubs", "diamonds" };

	return suit[currentCard->Suit];
}

char* getRank(Card currentCard)
{
	char* rank[] = { "two", "three", "four", "five", "six", "seven",
		"eight", "nine", "ten", "jack", "queen", "king", "ace" };

	return rank[currentCard->Rank];
}

int getNumSuit(Card currentCard)
{
	return currentCard->Suit;
}

int getNumRank(Card currentCard)
{
	return currentCard->Rank;
}

Card getNextCard(Card currentCard)
{
	return currentCard->next;
}

void setNextCard(Card currentCard, Card nextCard)
{
	currentCard->next = nextCard;
}

void freeCard(Card currentCard)
{
	free(currentCard);
}
