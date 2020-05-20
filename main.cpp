#include <iostream>
#include "splashkit.h"
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
        refresh_screen();
    }
}

int main(int argc, char* argv[]) {
    window a = open_window("Casino BlackJack", 800, 600);
    while (!window_close_requested(a)) 
    {
        clear_screen(COLOR_GREEN);
        draw_line(COLOR_BLACK, 0, current_window_height() / 2, current_window_width(), current_window_height() / 2);
        refresh_screen();
        Deck playingDeck;
        Player dealer(0, playingDeck);
        Player p1(1, playingDeck);
        vector<Player*> players;
        players.push_back(&p1);
        players.push_back(&dealer);

        p1.Hit();
        p1.Hit();
        dealer.Hit();
        outputCards(players);

    // Game Loop
    bool gameOver = false;
    bool dealerRevealedCard = false;
    while (!gameOver) {
        if (dealer.getTotal() == 21) {
            p1.Holding = true;
        }
        while (!p1.Holding && !gameOver) {
            if (p1.getTotal() == 21) {
                cout << "BLACKJACK! You got 21. You Win!" << endl;
                gameOver = true;
                break;
            }
            if (p1.PlayerCards.size() == 5) {
                cout << "5 CARDS! You Hit 5 cards, House Rules... You Win!" << endl;
                gameOver = true;
                break;
            }
            cout << "Would you like to HIT or HOLD?" << endl;
            string choice = "";
            bool validInput = false;
            while (!validInput && !gameOver) {
                cin >> choice;
                printLine();
                if (choice == "HIT") {
                    validInput = true;
                    p1.Hit();
                    cout << "Player has hit... (" << p1.PlayerCards.back().name() << ")" << endl;
                    outputCards(players);
                    if (p1.getTotal() > 21) {
                        cout << "You Busted! Game Over..." << endl;
                        gameOver = true;
                    }
                } else if (choice == "HOLD") {
                    validInput = true;
                    p1.Holding = true;
                } else {
                    cout << "Invalid Input. Please enter either 'HIT' or 'HOLD'" << endl;
                }
                outputCards(players);
            }
        }

        if (!gameOver) {
            if (!dealerRevealedCard) {
                // Dealers Second Card
                dealer.Hit();
                cout << "Dealer has revealed their second card... (" << dealer.PlayerCards.back().name() << ")" << endl;
                dealerRevealedCard = true;
                outputCards(players);
            }

            // Once the Player Holds:
            if (dealer.getTotal() > 21) {
                cout << "You Win! Dealer has busted..." << endl;
                outputCards(players);
                gameOver = true;
            } else if (dealer.getTotal() > p1.getTotal()) {
                cout << "You Lose! Dealer has scored better..." << endl;
                outputCards(players);
                gameOver = true;
            } else if (dealer.getTotal() < 17) {
                dealer.Hit();
                cout << "Dealer has hit... (" << dealer.PlayerCards.back().name() << ")" << endl;
                outputCards(players);
            } else if (dealer.getTotal() == p1.getTotal() && dealer.getTotal() >= 17) {
                cout << "You Drew! Both you and the dealer scored the same..." << endl;
                outputCards(players);
                gameOver = true;
            } else { 
                cout << "You Win! Dealer has stopped Hitting at 17+..." << endl;
                outputCards(players);
                gameOver = true;
            }   
            delay(1000);
            }
        }
        delay(1000);
    }
        return 0;
}