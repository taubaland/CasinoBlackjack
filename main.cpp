#include <iostream>
#include "Headers/Deck.h"
#include "Headers/Player.h"

using namespace std;

void printLine() {
    cout << endl;
}

void outputCards(vector<Player*> players) {
    for (int i = 0; i < players.size(); i++) {
        players[i]->PrintCards();
        printLine();
    }
}

int main(int argc, char* argv[]) {

    Deck playingDeck;
    Player dealer(0, playingDeck);
    Player p1(1, playingDeck);
    vector<Player*> players;
    players.push_back(&p1);
    players.push_back(&dealer);

    p1.Hit();
    p1.Hit();
    dealer.Hit();
    dealer.Hit();
     
    outputCards(players);

    // Game Loop
    bool gameOver = false;
    while (!gameOver) {
        if (dealer.getTotal() == 21) {
            p1.Holding = true;
        }
        while (!p1.Holding) {
            cout << "Would you like to HIT or HOLD?" << endl;
            string choice = "";
            bool validInput = false;
            while (!validInput) {
                cin >> choice;
                printLine();
                if (choice == "HIT") {
                    p1.Hit();
                    outputCards(players);
                    if (p1.getTotal() > 21) {
                        cout << "You Busted!" << endl;
                        gameOver = true;
                    }
                    validInput = true;
                } else if (choice == "HOLD") {
                    p1.Holding = true;
                    validInput = true;
                } else {
                    cout << "Invlaid Input. Please enter either 'HIT' or 'HOLD'" << endl;
                }
            }
        }
        if (dealer.getTotal() > 21) {
            cout << "You Win! Dealer has busted..." << endl;
            outputCards(players);
            gameOver = true;
        } else if (dealer.getTotal() >= p1.getTotal()) {
            cout << "You Lose! Dealer has scored better or equal to player:" << endl;
            outputCards(players);
            gameOver = true;
        } else {
            dealer.Hit();
            cout << "Dealer has hit..." << endl;
        }
    }
    return 0;
}