#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SUITS 4
#define RANKS 13
#define MAX_SCORE 21
#define DEALER_STANDS 17
#define PLAYERS 2 // both the player and the dealer
#define PLAYER 0
#define DEALER 1

void initialize_game(bool deck[SUITS][RANKS], bool hand[PLAYERS][SUITS][RANKS]);
void shuffle_deck(bool deck[SUITS][RANKS]);
void deal_initial_cards(bool deck[SUITS][RANKS], bool hand[PLAYERS][SUITS][RANKS]);
void show_dealer_initial_card(bool hand[SUITS][RANKS]);
int deal_card(bool deck[SUITS][RANKS], bool hand[SUITS][RANKS]);
void show_hand(bool hand[SUITS][RANKS], bool isDealer);
int calculate_hand_sum(bool hand[SUITS][RANKS]);
bool check_for_blackjack(int sum);
void compare_hands(int playerSum, int dealerSum);

void initialize_game(bool deck[SUITS][RANKS], bool hand[PLAYERS][SUITS][RANKS]) {
    shuffle_deck(deck);
    deal_initial_cards(deck, hand);
}

void shuffle_deck(bool deck[SUITS][RANKS]) {
    for (int suit = 0; suit < SUITS; suit++) {
        for (int rank = 0; rank < RANKS; rank++) {
            deck[suit][rank] = false;
        }
    }
}
void deal_initial_cards(bool deck[SUITS][RANKS], bool hand[PLAYERS][SUITS][RANKS]) {
    for (int player = 0; player < PLAYERS; player++) {
        for (int card = 0; card < 2; card++) { // Deal 2 cards to each player
            deal_card(deck, hand[player]);
        }
    }
}
void show_dealer_initial_card(bool hand[SUITS][RANKS]) {
    const char *suits[SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    const char *ranks[RANKS] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    
    printf("Dealer's initial card:\n");
    for (int suit = 0; suit < SUITS; suit++) {
        for (int rank = 0; rank < RANKS; rank++) {
            if (hand[suit][rank]) {
                printf("%s of %s\n", ranks[rank], suits[suit]);
                return; // Exit after showing the first card
            }
        }
    }
}

int deal_card(bool deck[SUITS][RANKS], bool hand[SUITS][RANKS]) {
    int suit, rank;
    do {
        suit = rand() % SUITS;
        rank = rand() % RANKS;
    } while (deck[suit][rank]); // Ensure we pick an undealt card

    deck[suit][rank] = true; // Mark card as dealt in the deck
    hand[suit][rank] = true; // Add card to player's hand
    return rank; // Return rank for any potential use
}
void show_hand(bool hand[SUITS][RANKS], bool isDealer) {
    const char *suits[SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    const char *ranks[RANKS] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    printf("%s's hand:\n", isDealer ? "Dealer" : "Player");
    for (int suit = 0; suit < SUITS; suit++) {
        for (int rank = 0; rank < RANKS; rank++) {
            if (hand[suit][rank]) {
                printf("%s of %s, ", ranks[rank], suits[suit]);
            }
        }
    }
    printf("\n");
}
int calculate_hand_sum(bool hand[SUITS][RANKS]) {
    int sum = 0, aces = 0;
    for (int suit = 0; suit < SUITS; suit++) {
        for (int rank = 0; rank < RANKS; rank++) {
            if (hand[suit][rank]) {
                if (rank == 0) {
                    aces++;
                    sum += 11;
                } else if (rank >= 10) {
                    sum += 10;
                } else {
                    sum += rank + 1;
                }
            }
        }
    }

    while (sum > MAX_SCORE && aces > 0) {
        sum -= 10; // Convert an Ace from 11 to 1
        aces--;
    }
    return sum;
}
bool check_for_blackjack(int sum) {
    return sum == MAX_SCORE;
}
void compare_hands(int playerSum, int dealerSum) {
    if (check_for_blackjack(playerSum) && check_for_blackjack(dealerSum)) {
        printf("Both player and dealer have blackjack. It's a tie!\n");
    } else if (check_for_blackjack(playerSum)) {
        printf("BLACKJACK! YOU WIN!\n");
    } else if (check_for_blackjack(dealerSum)) {
        printf("Dealer has blackjack. Dealer wins.\n");
    } else if (playerSum > MAX_SCORE) {
        printf("Player busts. Dealer wins.\n");
    } else if (dealerSum > MAX_SCORE) {
        printf("Dealer busts. You wins!\n");
    } else if (playerSum > dealerSum) {
        printf("Player wins with %d against Dealer's %d.\n", playerSum, dealerSum);
    }
}
