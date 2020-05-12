#pragma once
#include "Card.h"
#include <vector>
#include <string>

class Deck {
private:
    // Private Variables
    int const static cardLimit = 52;
    std::vector<Card> cards;

public:
    // Constructor
    Deck();

    // Return Methods (const)
    int remaining() const;

    // Methods
    void generateCards();
    Card draw();
};