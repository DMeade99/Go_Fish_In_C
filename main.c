#include <stdio.h>
#include "deck.h"
#include "card.h"

int main()
{
	int userChoice = 0;
	int option = 0;

	printf("Welcome to Go Fish!\n\n");
	printf("Please select an option below to continue:\n\n");
	printf("1. Play a new game\n");
	printf("2. Exit the program\n");
	scanf("%d", &userChoice);

	while (userChoice == 1)
	{
		// Create player and computer decks
		Deck playerHand = createEmptyDeck();
		Deck playerBooks = createEmptyDeck();
		Deck computerHand = createEmptyDeck();
		Deck computerBooks = createEmptyDeck();
		Deck fullDeck = createFullDeck();

		// Deal initial cards to player
		dealCards(fullDeck, playerHand, 7);
		dealCards(fullDeck, computerHand, 7);

		// TEST PRINT
		printf("\nPlayer:\n");
		printDeck(playerHand);
		printf("\nComputer:\n");
		printDeck(computerHand);
		getchar();

		// Begin turns
		while (gameOver(playerHand, computerHand, fullDeck) == 0)
		{
			// Player turn
			// Print player hand
			printf("\n");
			printDeck(playerHand);

			// Player options
			printf("Select an option below:\n\n");
			printf("1. Make a guess\n");
			printf("2. View your books\n");
			printf("3. View you opponent's books\n\n");
			scanf("%d", &option);

			while (option == 2)
			{
				if (isEmpty(playerBooks) == 1)
				{
					printf("There are no cards there...yet\n\n");
				}
				else
				{
					printDeck(playerBooks);
				}
				printf("Select an option below:\n\n");
				printf("1. Make a guess\n");
				printf("2. View your books\n");
				printf("3. View you opponent's books\n\n");
				scanf("%d", &option);
			}

			while (option == 3)
			{
				if (isEmpty(computerBooks) == 1)
				{
					printf("There are no cards there...yet\n\n");
				}
				else
				{
					printDeck(computerBooks);
				}
				printf("Select an option below:\n\n");
				printf("1. Make a guess\n");
				printf("2. View your books\n");
				printf("3. View your opponent's books\n\n");
				scanf("%d", &option);
			}

			if (option == 1)
			{
				makePlayerGuess(playerHand, computerHand, fullDeck);
			}


			// Check for books
			getBooks(playerHand, playerBooks);

			// Computer turn
			makeComputerGuess(computerHand, playerHand, fullDeck);
			getBooks(computerHand, computerBooks);
		}

		if (getLength(playerBooks) > getLength(computerBooks))
		{
			printf("Great game!\n");
			printf("Please select an option below to continue:\n\n");
			printf("1. Play a new game\n");
			printf("2. Exit the program\n");
			scanf("%d", &userChoice);
			freeDeck(fullDeck);
			freeDeck(playerHand);
			freeDeck(playerBooks);
			freeDeck(computerHand);
			freeDeck(computerBooks);
		}
		else
		{
			printf("That was a noble effort.\n");
			printf("Please select an option below to continue:\n\n");
			printf("1. Play a new game\n");
			printf("2. Exit the program\n");
			scanf("%d", &userChoice);
			freeDeck(fullDeck);
			freeDeck(playerHand);
			freeDeck(playerBooks);
			freeDeck(computerHand);
			freeDeck(computerBooks);
		}

	}

	return 0;
}