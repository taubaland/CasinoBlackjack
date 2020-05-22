#include <iostream>
#include "splashkit.h"
#include "Headers/Deck.h"
#include "Headers/Player.h"
#include <cstdlib>

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

void printText(bitmap textField, string text) {
    clear_bitmap(textField, COLOR_GREEN);
    draw_text_on_bitmap(textField, text, COLOR_BLACK, 0, 0);
    draw_bitmap(textField, current_window_width() / 3.0, current_window_height() / 2.0 + 10);
    refresh_screen();
}

int main(int argc, char* argv[]) {
    window a = open_window("Casino BlackJack", 800, 600);
    while (!window_close_requested(a)) 
    {
        clear_screen(COLOR_GREEN);
        draw_line(COLOR_BLACK, 0, current_window_height() / 2, current_window_width(), current_window_height() / 2);

        
        bitmap hit = load_bitmap("hit", "images/hit.png");
        bitmap hold = load_bitmap("hold", "images/hold.png");

        // Images to be added - (ALEX)
        bitmap restart = load_bitmap("restart", "images/restart.png");
        bitmap exit = load_bitmap("exit", "images/restart.png");

        bitmap textField = create_bitmap("textField", 400, 20);
        draw_bitmap(hit, current_window_width() - bitmap_width(hit) - 10, current_window_height() / 2 + 10);
        draw_bitmap(hold, current_window_width() - bitmap_width(hold) - 10, current_window_height() / 2 - bitmap_height(hold) - 10);

        draw_bitmap(restart, 10, current_window_height() / 2 + 10);
        draw_bitmap(exit, 10, current_window_height() / 2 - bitmap_height(exit) - 10);

        draw_bitmap(textField, current_window_width() / 3.0, current_window_height() / 2.0 + 10);

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
                printText(textField, "BLACKJACK!You got 21. You Win!");
                gameOver = true;
                break;
            }
            if (p1.PlayerCards.size() == 5) {
                printText(textField, "5 CARDS! You Hit 5 cards, House Rules... You Win!");
                gameOver = true;
                break;
            }
            printText(textField, "Would you like to HIT or HOLD?");

            //string choice = "";
            //bool validInput = false;
            process_events();
            while (/*!validInput &&*/ !gameOver) {
             //   cin >> choice;
                printLine();
                process_events();
                if (mouse_down(LEFT_BUTTON) && pixel_drawn_at_point(hit, mouse_position()) ) {
                    //validInput = true;
                    p1.Hit();
                    //cout << "Player has hit... (" << p1.PlayerCards.back().name() << ")" << endl;
                    printText(textField, "Player has hit.");

                    outputCards(players);
                    if (p1.getTotal() > 21) {
                        printText(textField, "You Busted! Game Over...");
                        gameOver = true;
                    }
                } else if (mouse_down(LEFT_BUTTON) && pixel_drawn_at_point(hold, mouse_position())) {
                    //validInput = true;
                    p1.Holding = true;
                } else {
                //    cout << "Invalid Input. Please enter either 'HIT' or 'HOLD'" << endl;
                }
                cout << "1";
                process_events();
                if (point_in_rectangle(mouse_position(), bitmap_cell_rectangle(hit)))
                {
                    cout << "2";
                }
                //outputCards(players);
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
                printText(textField, "You Win! Dealer has busted...");

                //cout << "You Win! Dealer has busted..." << endl;
                outputCards(players);
                gameOver = true;
            } else if (dealer.getTotal() > p1.getTotal()) {
                printText(textField, "You Lose! Dealer has scored better...");

                //cout << "You Lose! Dealer has scored better..." << endl;
                outputCards(players);
                gameOver = true;
            } else if (dealer.getTotal() < 17) {
                dealer.Hit();

                //cout << "Dealer has hit... (" << dealer.PlayerCards.back().name() << ")" << endl;
                outputCards(players);
            } else if (dealer.getTotal() == p1.getTotal() && dealer.getTotal() >= 17) {
                printText(textField, "You Drew! Both you and the dealer scored the same...");

                //cout << "You Drew! Both you and the dealer scored the same..." << endl;
                outputCards(players);
                gameOver = true;
            } else {
                printText(textField, "You Win! Dealer has stopped Hitting at 17+...");

                //cout << "You Win! Dealer has stopped Hitting at 17+..." << endl;
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