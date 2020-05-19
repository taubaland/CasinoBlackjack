#include "../Headers/Deck.h"
#include <vector>
#include <string>

using namespace std;

class Player {
private:
    int CurrentTotal;
    Deck* CurrentDeck;

public:
    // Variables
    int ID;
    bool Win;
    bool Holding;
    vector<Card> PlayerCards;

    // Constructors
    Player(int id, Deck& deck);

    // Methods
    void Hit();
    void Hold();
    void PrintCards();
    int getTotal();
};