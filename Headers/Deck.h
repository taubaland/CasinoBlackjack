#pragma once
#include "Card.h"
#include <vector>
#include <string>

using namespace std;

class Deck {
private:
    // Private Variables
    int const static cardLimit = 52;
    vector<Card> cards;

public:
    // Constructor
    Deck();

    // Return Methods (const)
    int remaining() const;

    // Methods
    void generateCards();
    Card draw();
};