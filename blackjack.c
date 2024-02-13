#include <stdio.h>
#include <stdlib.h>

#include "blackjack.h" 

int main() {
    int playAgain = 1;
    do {
        bool deck[SUITS][RANKS] = {false};
        bool hand[PLAYERS][SUITS][RANKS] = {false};
        int playerSum, dealerSum;
        char choice;

        srand(time(NULL)); // Initialize random seed

        initialize_game(deck, hand);
        show_dealer_initial_card(hand[DEALER]);
        show_hand(hand[PLAYER], false); // Show player's hand
        playerSum = calculate_hand_sum(hand[PLAYER]);
        dealerSum = calculate_hand_sum(hand[DEALER]); // Initial sum for the dealer

        // Player's turn
        while (true) {
            printf("Hit (h) or stand (s)?: ");
            scanf(" %c", &choice);
            if (choice == 'h') {
                deal_card(deck, hand[PLAYER]);
                show_hand(hand[PLAYER], false);
                playerSum = calculate_hand_sum(hand[PLAYER]);
                if (playerSum > MAX_SCORE) {
                    printf("Bust! Game over.\n");
                    return 0;
                }
            } else {
                break;
            }
        }

        // Dealer's turn
        while (dealerSum < DEALER_STANDS) {
            deal_card(deck, hand[DEALER]);
            dealerSum = calculate_hand_sum(hand[DEALER]);
        }
        show_hand(hand[DEALER], true); // Show dealer's hand

        // Determine the winner
        compare_hands(playerSum, dealerSum);

        printf("Play Again? -> 1\nExit -> 0\n");
        scanf(" %d", &playAgain);
    } while (playAgain == 1);
    return 0;
}