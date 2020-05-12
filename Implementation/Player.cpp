#include <iostream>
#include "../Headers/Player.h"

Player::Player(int id, Deck& deck) {
    ID = id;
    CurrentTotal = 0;
    Win = false;
    Holding = false;
    CurrentDeck = &deck;
};

void Player::Hit() {
    Card newCard = CurrentDeck->draw();
    CurrentTotal += newCard.value();
    PlayerCards.push_back(newCard);
}

void Player::Hold() {
    Holding = true;
}

int Player::getTotal() {
    return CurrentTotal;
}

void Player::PrintCards() {
    for (int i = 0; i < PlayerCards.size(); i++) {
        cout << PlayerCards[i].name() << endl;
    }
    cout << "Total: " << getTotal() << endl;
}