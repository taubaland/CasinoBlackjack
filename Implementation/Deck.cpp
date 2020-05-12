#include "../Headers/Deck.h"
#include <algorithm>
#include <time.h>

using namespace std;

Deck::Deck() {
    generateCards();
}

int Deck::remaining() const {
    return cards.size();
}

void Deck::generateCards() {
    while (!cards.empty()) {
        cards.pop_back();
    }

    string suits[4] = {"Diamonds", "Hearts", "Clubs", "Spades"};
    string names[13] = {"2", "3", "4",
                             "5", "6", "7", "8",
                             "9", "10", "A", "J", "Q", "K"};

    // for every suit
    for (int i = 0; i < 4; i++) {
        // for every card
        for (int j = 2; j <= 14; j++) {
            // create new card and enqueue
            Card newCard(j, names[j-2], suits[i]);
            cards.push_back(newCard);
        }
    }

    // Shuffle Deck
    srand(time(NULL));
    for (int i = 0; i < cards.size() - 1; i++) {
        int random = i + rand() % (cards.size() - i);
        swap(cards[i], cards[random]);
    }
}

Card Deck::draw() {
    Card& temp = cards.back();
    cards.pop_back();
    return temp;
}