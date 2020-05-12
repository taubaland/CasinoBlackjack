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
    PlayerCards.push_back(newCard);
}

void Player::Hold() {
    Holding = true;
}

int Player::getTotal() {
    for (int i = 0; i < PlayerCards.size(); i++) {
        Card card = PlayerCards[i];
        if (card.value() > 11) {
            CurrentTotal += 10;
        } else if (card.value() == 11) {
            if (CurrentTotal + 11 > 21) {
                CurrentTotal += 1;
            } else {
                CurrentTotal += 11;
            }
        } else {
            CurrentTotal += card.value();
        }
    }

    return CurrentTotal;
}

void Player::PrintCards() {
    for (int i = 0; i < PlayerCards.size(); i++) {
        cout << PlayerCards[i].name() << endl;
    }
    cout << "Total: " << getTotal() << endl;
}