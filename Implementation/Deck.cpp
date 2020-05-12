#include "../Headers/Deck.h"
#include <algorithm>
#include <time.h>

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

    std::string suits[4] = {"Diamonds", "Hearts", "Clubs", "Spades"};
    std::string names[13] = {"Ace", "Two", "Three", "Four",
                             "Five", "Six", "Seven", "Eight",
                             "Nine", "Ten", "Jack", "Queen", "King"};

    // for every suit
    for (int i = 0; i < 4; i++) {
        // for every card
        for (int j = 1; j <= 13; j++) {
            // create new card and enqueue
            Card newCard(j, names[j-1], suits[i]);
            cards.push_back(newCard);
        }
    }

    // Shuffle Deck
    srand(time(NULL));
    for (int i = 0; i < cards.size() - 1; i++) {
        int random = i + rand() % (cards.size() - i);
        std::swap(cards[i], cards[random]);
    }
}

Card Deck::draw() {
    Card& temp = cards.back();
    cards.pop_back();
    return temp;
}