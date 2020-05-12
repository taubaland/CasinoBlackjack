#include "../Headers/Deck.h"
#include <vector>

using namespace std;

class Player {
private:
    int CurrentTotal;
    Deck* CurrentDeck;
    vector<Card> PlayerCards;

public:
    // Variables
    int ID;
    bool Win;
    bool Holding;

    // Constructors
    Player(int id, Deck& deck);

    // Methods
    void Hit();
    void Hold();
    void PrintCards();
    int getTotal();
};