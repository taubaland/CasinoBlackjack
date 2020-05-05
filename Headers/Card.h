#pragma once
#include <string>

class Card {
private:
    // Private Variables
    int faceValue;
    std::string cardName;
    std::string cardSuit;
    

public:
    // Constructor
    Card();
    Card(int value, std::string name, std::string suit);

    // Return Methods (const)
    int value() const;
    std::string name() const;
};