#pragma once
#include <string>

using namespace std;

class Card {
private:
    // Private Variables
    int faceValue;
    string cardName;
    string cardSuit;
    
public:
    // Constructor
    Card();
    Card(int value, std::string name, std::string suit);

    // Return Methods (const)
    int value() const;
    string name() const;
};