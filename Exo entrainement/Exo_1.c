#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define DECK_SIZE 52
#define SUITS 4
#define RANKS 13
#define PILES 7

typedef struct {
    char suit;
    char rank;
    bool faceUp;
} Card;

typedef struct {
    Card cards[DECK_SIZE];
    int top;
} Pile;

typedef struct {
    Pile tableau[PILES];
    Pile stock;
    Pile waste;
    Pile foundation[SUITS];
} Game;

void initializeDeck(Card *deck);
void shuffleDeck(Card *deck);
void initializeGame(Game *game);
void dealCards(Game *game);
void printGame(const Game *game);
void moveCard(Pile *source, Pile *destination);
void drawFromStock(Game *game);
bool isMoveValid(const Card *sourceCard, const Card *destCard);
void moveToFoundation(Game *game, int tableauIndex);
void playGame(Game *game);
bool hasWon(const Game *game);

int main() {
    Game game;
    initializeGame(&game);
    dealCards(&game);
    printGame(&game);

    playGame(&game);

    return 0;
}

void initializeDeck(Card *deck) {
    char suits[SUITS] = {'H', 'D', 'C', 'S'}; // Hearts, Diamonds, Clubs, Spades
    char ranks[RANKS] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

    for (int i = 0; i < DECK_SIZE; ++i) {
        deck[i].suit = suits[i / RANKS];
        deck[i].rank = ranks[i % RANKS];
        deck[i].faceUp = false;
    }
}

void shuffleDeck(Card *deck) {
    srand(time(NULL));
    for (int i = DECK_SIZE - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void initializeGame(Game *game) {
    Card deck[DECK_SIZE];
    initializeDeck(deck);
    shuffleDeck(deck);

    for (int i = 0; i < PILES; ++i) {
        game->tableau[i].top = 0;
    }
    game->stock.top = 0;
    game->waste.top = 0;
    for (int i = 0; i < SUITS; ++i) {
        game->foundation[i].top = 0;
    }

    for (int i = 0; i < DECK_SIZE; ++i) {
        game->stock.cards[game->stock.top++] = deck[i];
    }
}

void dealCards(Game *game) {
    for (int i = 0; i < PILES; ++i) {
        for (int j = 0; j <= i; ++j) {
            game->tableau[i].cards[game->tableau[i].top++] = game->stock.cards[--game->stock.top];
            if (j == i) {
                game->tableau[i].cards[game->tableau[i].top - 1].faceUp = true;
            }
        }
    }
}

void printCard(const Card *card) {
    if (card->faceUp) {
        printf("%c%c ", card->rank, card->suit);
    } else {
        printf("XX ");
    }
}

void printPile(const Pile *pile) {
    for (int i = 0; i < pile->top; ++i) {
        printCard(&pile->cards[i]);
    }
    printf("\n");
}

void printGame(const Game *game) {
    printf("Tableau:\n");
    for (int i = 0; i < PILES; ++i) {
        printf("Pile %d: ", i + 1);
        printPile(&game->tableau[i]);
    }

    printf("Stock: ");
    printPile(&game->stock);

    printf("Waste: ");
    printPile(&game->waste);

    for (int i = 0; i < SUITS; ++i) {
        printf("Foundation %d: ", i + 1);
        printPile(&game->foundation[i]);
    }
}

void moveCard(Pile *source, Pile *destination) {
    if (source->top > 0) {
        destination->cards[destination->top++] = source->cards[--source->top];
    }
}

void drawFromStock(Game *game) {
    if (game->stock.top > 0) {
        Card drawnCard = game->stock.cards[--game->stock.top];
        drawnCard.faceUp = true;
        game->waste.cards[game->waste.top++] = drawnCard;
    } else {
        while (game->waste.top > 0) {
            Card returnedCard = game->waste.cards[--game->waste.top];
            returnedCard.faceUp = false;
            game->stock.cards[game->stock.top++] = returnedCard;
        }
    }
}

bool isMoveValid(const Card *sourceCard, const Card *destCard) {
    if (sourceCard->faceUp && (!destCard || destCard->faceUp)) {
        int sourceRank = sourceCard->rank == 'A' ? 1 : sourceCard->rank == 'T' ? 10 : sourceCard->rank == 'J' ? 11 : sourceCard->rank == 'Q' ? 12 : sourceCard->rank == 'K' ? 13 : sourceCard->rank - '0';
        int destRank = destCard ? (destCard->rank == 'A' ? 1 : destCard->rank == 'T' ? 10 : destCard->rank == 'J' ? 11 : destCard->rank == 'Q' ? 12 : destCard->rank == 'K' ? 13 : destCard->rank - '0') : 0;
        bool differentColor = destCard ? ((sourceCard->suit == 'H' || sourceCard->suit == 'D') != (destCard->suit == 'C' || destCard->suit == 'S')) : true;
        return (sourceRank == destRank + 1) && differentColor;
    }
    return false;
}

void moveToFoundation(Game *game, int tableauIndex) {
    if (game->tableau[tableauIndex].top > 0) {
        Card *cardToMove = &game->tableau[tableauIndex].cards[game->tableau[tableauIndex].top - 1];
        for (int i = 0; i < SUITS; ++i) {
            if (game->foundation[i].top == 0 && cardToMove->rank == 'A') {
                moveCard(&game->tableau[tableauIndex], &game->foundation[i]);
                return;
            } else if (game->foundation[i].top > 0) {
                Card *topCard = &game->foundation[i].cards[game->foundation[i].top - 1];
                if (cardToMove->suit == topCard->suit && cardToMove->rank == topCard->rank + 1) {
                    moveCard(&game->tableau[tableauIndex], &game->foundation[i]);
                    return;
                }
            }
        }
    }
}

void playGame(Game *game) {
    char command[10];
    int sourcePile, destPile;

    while (true) {
        printf("Enter command (move, draw, foundation, quit): ");
        scanf("%s", command);

        if (strcmp(command, "move") == 0) {
            printf("Enter source pile and destination pile: ");
            scanf("%d %d", &sourcePile, &destPile);
            if (sourcePile >= 1 && sourcePile <= PILES && destPile >= 1 && destPile <= PILES) {
                if (isMoveValid(&game->tableau[sourcePile - 1].cards[game->tableau[sourcePile - 1].top - 1], game->tableau[destPile - 1].top > 0 ? &game->tableau[destPile - 1].cards[game->tableau[destPile - 1].top - 1] : NULL)) {
                    moveCard(&game->tableau[sourcePile - 1], &game->tableau[destPile - 1]);
                } else {
                    printf("Invalid move.\n");
                }
                printGame(game);
            } else {
                printf("Invalid pile numbers.\n");
            }
        } else if (strcmp(command, "draw") == 0) {
            drawFromStock(game);
            printGame(game);
        } else if (strcmp(command, "foundation") == 0) {
            printf("Enter tableau pile number to move to foundation: ");
            scanf("%d", &sourcePile);
            if (sourcePile >= 1 && sourcePile <= PILES) {
                moveToFoundation(game, sourcePile - 1);
                printGame(game);
            } else {
                printf("Invalid pile number.\n");
            }
        } else if (strcmp(command, "quit") == 0) {
            break;
        } else {
            printf("Invalid command.\n");
        }

        if (hasWon(game)) {
            printf("Congratulations! You've won the game!\n");
            break;
        }
    }
}

bool hasWon(const Game *game) {
    for (int i = 0; i < SUITS; ++i) {
        if (game->foundation[i].top < RANKS) {
            return false;
        }
    }
    return true;
}