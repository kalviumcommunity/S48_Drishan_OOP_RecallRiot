#include <iostream>
#include <vector>

using namespace std;

class Card {
private:
    char value;
    bool faceUp;
    static int flipCount;  // Static variable to count card flips

public:
    // Constructor
    Card(char v) : value(v), faceUp(false) {}

    // Member function to flip the card
    void flip() {
        faceUp = !faceUp;
        flipCount++;  // Increment flip count each time a card is flipped
    }

    // Member function to get the card's value
    char getValue() const {
        return value;
    }

    // Static function to get the flip count
    static int getFlipCount() {
        return flipCount;
    }
};

int Card::flipCount = 0;  // Initialize static flip count

class MemoryGame {
private:
    vector<Card*> cards;  // Vector to hold pointers to Card objects
    static int totalCards;  // Static variable to track total cards added

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
        totalCards++;  // Increment total cards count
    }

    // Member function to display the values of the cards
    void displayCards() const {
        for (const auto& card : cards) {
            cout << card->getValue() << " ";
        }
        cout << endl;
    }

    // Static function to get the total number of cards
    static int getTotalCards() {
        return totalCards;
    }
};

int MemoryGame::totalCards = 0;  // Initialize static total cards count

int main() {
    // Instantiating object dynamically
    MemoryGame* game = new MemoryGame();

    // Adding cards to the game
    game->addCard('A');
    game->addCard('B');

    // Displaying the cards
    game->displayCards();

    // Displaying the total cards and flip count
    cout << "Total cards: " << MemoryGame::getTotalCards() << endl;
    cout << "Total flips: " << Card::getFlipCount() << endl;

    // Deleting the dynamically allocated game object
    delete game;

    return 0;
}
