#include <iostream>
#include "Headers/Deck.h"
#include "Headers/Player.h"

using namespace std;

int main(int argc, char* argv[]) {

    Deck playingDeck;
    Player dealer(0, playingDeck);
    Player p1(1, playingDeck);
    
    // p1.Hit();
    // dealer.Hit();
    // p1.Hit();
    // cout << "Player 1 Cards:" << endl;
    // p1.PrintCards();
    // cout << endl;

    // cout << "Dealer Cards:" << endl;
    // dealer.PrintCards();
    // dealer.Hit();

    return 0;
}