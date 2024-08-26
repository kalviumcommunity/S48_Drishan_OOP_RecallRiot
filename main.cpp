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
    // Create an array of Card objects
    Card cardArray[3] = { Card('A'), Card('B'), Card('C') };

    // Flip and display the cards using the array
    for (int i = 0; i < 3; ++i) {
        cardArray[i].flip();
        cout << "Card " << i + 1 << ": ";
        cout << cardArray[i].getValue() << " (Flipped)" << endl;
    }

    // Instantiate MemoryGame object
    MemoryGame game;

    // Add cards to the game using the array
    for (int i = 0; i < 3; ++i) {
        game.addCard(cardArray[i].getValue());
    }

    // Displaying the cards in the game
    game.displayCards();

    return 0;
}
