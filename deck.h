#ifndef DECK_H
#define DECK_H

#include <stdbool.h>
#include "card.h"

typedef struct deck *Deck;

Deck createEmptyDeck();

Deck createFullDeck();

void append(Deck currentDeck, int Rank, int Suit);

void prepend(Deck currentDeck, int Rank, int Suit);

void removeAt(Deck currentDeck, int position);

int getLength(Deck currentDeck);

void printDeck(Deck currentDeck);

void shuffleDeck(Deck currentDeck, int times);

void mergeDeck(Deck currentDeck);

void merge(Card *head);

void partitionDeck(Card temp, Card *front, Card *back);

Card sortDeckRank(Card front, Card back);

Card sortDeckSuit(Card front, Card back);

void insertIntoHand(Deck hand, Card newCard);

void dealCards(Deck fullDeck, Deck hand, int numOfCards);

Card drawCard(Deck fullDeck);

Card getRandom(Deck currentDeck);

void makePlayerGuess(Deck playerDeck, Deck computerDeck, Deck fullDeck);

void makeComputerGuess(Deck computerDeck, Deck playerDeck, Deck fullDeck);

void getBooks(Deck currentHand, Deck bookDeck);

bool gameOver(Deck playerHand, Deck computerHand, Deck fullDeck);

bool isEmpty(Deck currentDeck);

void freeDeck(Deck currentDeck);

#endif
