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
        faceUp = !faceUp;
    }

    // Member function to get the card's value
    char getValue() const {
        return value;
    }
};

class MemoryGame {
private:
    vector<Card*> cards;  // Vector to hold pointers to Card objects

public:
    ~MemoryGame() {
        // Destructor to release dynamically allocated memory
        for (auto card : cards) {
            delete card;
        }
    }

    // Member function to add a card to the game
    void addCard(char value) {
        cards.push_back(new Card(value));  // Dynamically allocate memory for Card
    }

    // Member function to display the values of the cards
    void displayCards() const {
        for (const auto& card : cards) {
            cout << card->getValue() << " ";
        }
        cout << endl;
    }
};

int main() {
    // Instantiating object dynamically
    MemoryGame* game = new MemoryGame();

    // Adding cards to the game
    game->addCard('A');
    game->addCard('B');

    // Displaying the cards
    game->displayCards();

    // Deleting the dynamically allocated game object
    delete game;

    return 0;
}
