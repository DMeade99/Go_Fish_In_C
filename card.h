#ifndef CARD_H
#define CARD_H

typedef struct card *Card;

Card createCard(int Rank, int Suit, Card next);

char* getSuit(Card currentCard);

char* getRank(Card currentCard);

int getNumSuit(Card currentCard);

int getNumRank(Card currentCard);

Card getNextCard(Card currentCard);

void setNextCard(Card currentCard, Card nextCard);

void freeCard(Card currentCard);

#endif