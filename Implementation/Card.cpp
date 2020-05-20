#include "../Headers/Card.h"

using namespace std;

Card::Card(int value, std::string name, std::string suit) {
    cardName = name;
    cardSuit = suit;

    if (faceValue > 10) {
        faceValue = 10;
    } else {
        faceValue = value;
    }
}

int Card::value() const {
    return faceValue;
}

std::string Card::name() const {
    return cardName + " of " + cardSuit;
}

std::string Card::nameString() const {
    return cardName;
}

std::string Card::suit() const {
    return cardSuit;
}