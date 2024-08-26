#include <iostream>
#include <vector>

using namespace std;

class Card {
private:
    char value;
    bool faceUp;

public:
    // Constructor
    Card(char v) : value(v), faceUp(false) {}

    // Member function to flip the card
    void flip() {
         this->faceUp = !this->faceUp;  
    }

    // Member function to get the card's value
    char getValue() const {
         return this->value;
    }
};

class MemoryGame {
private:
    vector<Card> cards;

public:
    // Member function to add a card to the game
    void addCard(char value) {
        cards.push_back(Card(value));
    }

    // Member function to display the values of the cards
    void displayCards() const {
        for (const auto& card : cards) {
            cout << card.getValue() << " ";
        }
        cout << endl;
    }
};

int main() {
    // Instantiating objects
    MemoryGame game;

    // Adding cards to the game
    game.addCard('A');
    game.addCard('B');

    // Displaying the cards
    game.displayCards();

    return 0;
}
