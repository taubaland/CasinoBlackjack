#include <iostream>
#include "splashkit.h"
#include "Headers/Deck.h"
#include "Headers/Player.h"
#include <cstdlib>

using namespace std;

void outputCards(vector<Player*> players) {
    for (int i = 0; i < players.size(); i++) {
        players[i]->PrintCards();
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
        
        // Bitmaps for Buttons and Output Text

        // Images to be added - (ALEX)
        bitmap restart = load_bitmap("restart", "images/restart.png");
        bitmap exit = load_bitmap("exit", "images/restart.png");
        // **************
        bitmap hit = load_bitmap("hit", "images/hit.png");
        bitmap hold = load_bitmap("hold", "images/hold.png");
        bitmap textField = create_bitmap("textField", 400, 20);

        // Hit and Hold Buttons
        draw_bitmap(hit, current_window_width() - bitmap_width(hit) - 10, current_window_height() / 2 + 10);
        draw_bitmap(hold, current_window_width() - bitmap_width(hold) - 10, current_window_height() / 2 - bitmap_height(hold) - 10);

        // Restart and Exit Buttons
        draw_bitmap(restart, 10, current_window_height() / 2 + 10);
        draw_bitmap(exit, 10, current_window_height() / 2 - bitmap_height(exit) - 10);

        // Output Text
        draw_bitmap(textField, current_window_width() / 3.0, current_window_height() / 2.0 + 10);

        refresh_screen();

        // Deck and Player/Dealer Setup
        Deck playingDeck;
        Player dealer(0, playingDeck);
        Player p1(1, playingDeck);
        vector<Player*> players;

        // Add both player and dealer to players vector
        players.push_back(&p1);
        players.push_back(&dealer);

        // Hit 2 cards for player, 1 card for dealer
        p1.Hit();
        p1.Hit();
        dealer.Hit();

        // Output all players cards to screen
        outputCards(players);

    // Game Loop
    bool gameOver = false;
    bool dealerRevealedCard = false;

    while (!gameOver) {
        // Checks if player got 21
        if (p1.getTotal() == 21) {
                printText(textField, "BLACKJACK!You got 21. You Win!");
                gameOver = true;
                break;
            }

        // Checks if dealer got 21
        if (dealer.getTotal() == 21) {
            p1.Holding = true;
        }

        // Checks for user HIT or HOLD
        while (!p1.Holding && !gameOver) {

            // Checks for 5 card victory
            if (p1.PlayerCards.size() == 5) {
                printText(textField, "5 CARDS! You Hit 5 cards, House Rules... You Win!");
                gameOver = true;
                break;
            }

            // Outputs HIT or HOLD option
            printText(textField, "Would you like to HIT or HOLD?");
            process_events();

            // Checks for Gameover
            while (!gameOver) {
                process_events();

                // Needs editing:
                if (mouse_down(LEFT_BUTTON) && pixel_drawn_at_point(hit, mouse_position()) ) {
                    p1.Hit();
                    printText(textField, "Player has hit.");
                    outputCards(players);

                    // Checks for Blackjack
                    if (p1.getTotal() > 21) {
                        printText(textField, "You Busted! Game Over...");
                        gameOver = true;
                    }
                } else if (mouse_down(LEFT_BUTTON) && pixel_drawn_at_point(hold, mouse_position())) {
                    p1.Holding = true;
                }

                // Testing ************
                cout << "1";
                process_events();

                if (point_in_rectangle(mouse_position(), bitmap_cell_rectangle(hit)))
                {
                    cout << "2";
                }
                // End Testing *************
            }
        }

        // Checks for NOT Gameover
        if (!gameOver) {
            // Dealer hits their 2nd card:
            if (!dealerRevealedCard) {
                dealer.Hit();
                cout << "Dealer has revealed their second card... (" << dealer.PlayerCards.back().name() << ")" << endl;
                dealerRevealedCard = true;
                outputCards(players);
            }

            // Once the Player Holds:
            if (dealer.getTotal() > 21) {
                printText(textField, "You Win! Dealer has busted...");
                outputCards(players);
                gameOver = true;
            } else if (dealer.getTotal() > p1.getTotal()) {
                printText(textField, "You Lose! Dealer has scored better...");
                outputCards(players);
                gameOver = true;
            } else if (dealer.getTotal() < 17) {
                dealer.Hit();
                outputCards(players);
            } else if (dealer.getTotal() == p1.getTotal() && dealer.getTotal() >= 17) {
                printText(textField, "You Drew! Both you and the dealer scored the same...");
                outputCards(players);
                gameOver = true;
            } else {
                printText(textField, "You Win! Dealer has stopped Hitting at 17+...");
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