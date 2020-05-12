#include <iostream>
#include "Headers/Deck.h"

using namespace std;

int main(int argc, char* argv[]) {

    Deck testDeck;

    while (testDeck.remaining() != 0) {
        cout << testDeck.draw().name() << endl;
    }
    
    return 0;
}