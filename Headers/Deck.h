#pragma once
#include "Card.h"
#include <queue>

class Deck {
private:
    // Private Variables
    int const static cardLimit = 52;
    std::queue<Card> cards;

public:
    // Constructor
    Deck();

    // Return Methods (const)
    int remaining() const;

    // Methods
    void generateCards();
    Card draw();
};