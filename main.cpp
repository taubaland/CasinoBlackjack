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

void printText(bitmap textField, string text, int i) {
    clear_bitmap(textField, COLOR_GREEN);
    draw_text_on_bitmap(textField, text, COLOR_BLACK, 0, 0);
    draw_bitmap(textField, current_window_width() / 3.0, current_window_height() / 2.0 + i);
    refresh_screen();
}

int main(int argc, char* argv[]) {
    window a = open_window("Casino BlackJack", 800, 600);
    while (!window_close_requested(a)) 
    {
        clear_screen(COLOR_GREEN);
        draw_line(COLOR_BLACK, 0, current_window_height() / 2, current_window_width(), current_window_height() / 2);
        
        // Bitmaps for Buttons and Output Text
        bitmap restart = load_bitmap("restart", "images/Buttons/restart.png");
        bitmap exit = load_bitmap("exit", "images/Buttons/exit.png");
        bitmap hit = load_bitmap("hit", "images/Buttons/hit.png");
        bitmap hold = load_bitmap("hold", "images/Buttons/hold.png");
        bitmap textField = create_bitmap("textField", 400, 20);

        // Hit and Hold Buttons
        draw_bitmap(hit, current_window_width() - bitmap_width(hit) - 10, current_window_height() / 2 + 10);
        draw_bitmap(hold, current_window_width() - bitmap_width(hold) - 10, current_window_height() / 2 - bitmap_height(hold) - 10);

        // Restart and Exit Buttons
        draw_bitmap(restart, 10, current_window_height() / 2 + 10);
        draw_bitmap(exit, 10, current_window_height() / 2 - bitmap_height(exit) - 10);

        // Output Text
        draw_bitmap(textField, current_window_width() / 3.5, current_window_height() / 2.0 + 10);

        // Clickable Areas
        rectangle hitRect;
        hitRect.x = current_window_width() - bitmap_width(hit) - 10;
        hitRect.y = current_window_height() / 2 + 10;
        hitRect.width = 96;
        hitRect.height = 64;

        rectangle holdRect;
        holdRect.x = current_window_width() - bitmap_width(hold) - 10;
        holdRect.y = current_window_height() / 2 - bitmap_height(hold) - 10;
        holdRect.width = 96;
        holdRect.height = 64;

        rectangle restartRect;
        restartRect.x = 10;
        restartRect.y = current_window_height() / 2 + 10;
        restartRect.width = 96;
        restartRect.height = 64;
        
        rectangle exitRect;
        exitRect.x = 10;
        exitRect.y = current_window_height() / 2 - bitmap_height(exit) - 10;
        exitRect.width = 96;
        exitRect.height = 64;

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
            // Checks for user HIT or HOLD
            while (!gameOver && !p1.Holding) {
                // Outputs HIT or HOLD option
                printText(textField, "Dealer Score: " + to_string(dealer.getTotal()), -20);
                printText(textField, "Player Score: " + to_string(p1.getTotal()), 10);
                printText(textField, "Would you like to HIT or HOLD?", 30);

                // Checks if player got 21
                if (p1.getTotal() == 21) {
                    printText(textField, "BLACKJACK! You got 21... You Win!", 10);
                    gameOver = true;
                    break;
                }

                // Checks for Gameover
                while (!gameOver && !p1.Holding) {
                    // Checks for 5 card victory
                    if (p1.PlayerCards.size() == 5) {
                        printText(textField, "You Hit 5 cards, House Rules... You Win!", 10);
                        gameOver = true;
                        break;
                    }

                    process_events();
                    if (mouse_clicked(LEFT_BUTTON) && point_in_rectangle(mouse_position(), exitRect)) {
                        close_all_windows();
                        break;
                    }

                    // Needs editing:
                    if (mouse_clicked(LEFT_BUTTON) && point_in_rectangle(mouse_position(), hitRect)) {
                        p1.Hit();
                        printText(textField, "Player Score: " + to_string(p1.getTotal()), 10);
                        outputCards(players);

                        // Checks for Blackjack
                        if (p1.getTotal() > 21) {
                            printText(textField, "You Busted! Game Over...", 10);
                            gameOver = true;
                        }
                        if (p1.getTotal() == 21) {
                            printText(textField, "BLACKJACK! You got 21. You Win!", 10);
                            gameOver = true;
                            break;
                        }
                    } 
                    
                    if (mouse_clicked(LEFT_BUTTON) && point_in_rectangle(mouse_position(), holdRect)) {
                        p1.Holding = true;
                    }
                }
            }

            // Checks for NOT Gameover
            if (!gameOver) {
                printText(textField, "Player has selected HOLD.", 30);
                // Dealer hits their 2nd card:
                if (!dealerRevealedCard) {
                    dealer.Hit();
                    printText(textField, "Dealer Second Card: " + dealer.PlayerCards.back().name(), -40);
                    printText(textField, "Dealer Score: " + to_string(dealer.getTotal()), -20);
                    dealerRevealedCard = true;
                    outputCards(players);
                    delay(1700);
                }

                // Once the Player Holds:
                if (dealer.getTotal() > 21) {
                    printText(textField, "You Win! Dealer has busted...", 10);
                    outputCards(players);
                    gameOver = true;
                } else if (dealer.getTotal() > p1.getTotal()) {
                    printText(textField, "You Lose! Dealer has scored better...", 10);
                    outputCards(players);
                    gameOver = true;
                } else if (dealer.getTotal() < 17) {
                    dealer.Hit();
                    printText(textField, "Dealer Score: " + to_string(dealer.getTotal()), -20);
                    outputCards(players);
                } else if (dealer.PlayerCards.size() == 5) {
                    printText(textField, "You Lose! Dealer has drawn 5 cards...", 10);
                    gameOver = true;
                    break;
                } else if (dealer.getTotal() == p1.getTotal() && dealer.getTotal() >= 17) {
                    printText(textField, "You Drew! Both you and the dealer scored the same...", 10);
                    outputCards(players);
                    gameOver = true;
                } else {
                    printText(textField, "You Win! Dealer has stopped Hitting at 17+...", 10);
                    outputCards(players);
                    gameOver = true;
                }   
                    delay(1700);
                }
            }

            // Restart Button
            while (!(mouse_clicked(LEFT_BUTTON) && point_in_rectangle(mouse_position(), restartRect))) {
                printText(textField, "Restart: Play Again. Exit: Leave Game.", 30);
                process_events();
                if (mouse_clicked(LEFT_BUTTON) && point_in_rectangle(mouse_position(), exitRect)) {
                        close_all_windows();
                        break;
                }
            }
        }
    return 0;
}