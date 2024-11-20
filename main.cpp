#include <iostream>  
#include <algorithm>  // For std::shuffle
#include <random>     // For std::random_device and std::mt19937
#include <ctime>      // For seeding the random number generator

using namespace std;


// Class handling card-specific details
class Card {

class GameObject {
protected:
    static int remainingFlips;  // Static variable for tracking remaining flips
public:
    virtual void flip() = 0;  // Pure virtual function to be overridden in derived classes (Abstract Class)
    static int getRemainingFlips() {
        return remainingFlips;
    }
};

int GameObject::remainingFlips = 32;  // Initialize static variable with 32 flips

class Card : public GameObject {

private:
    char value;
    bool faceUp;

public:
    Card(char value) : value(value), faceUp(false) {} // Card handles only its state and behavior.

    // Accessor for card value
    char getValue() const {
        return value;
    }

    void flip() {
        faceUp = !faceUp; // Flipping logic specific to the card.
        flipCount++;

    // Mutator for flipping the card
    void flip() override {  // Overriding virtual function from GameObject
        faceUp = !faceUp;
        remainingFlips--;  // Decrement remaining flips every time a card is flipped

    }

    // Accessor for faceUp state
    bool isFaceUp() const {
        return faceUp;
    }

    static int getFlipCount() {
        return flipCount;
    }
};

int Card::flipCount = 0;

// Class managing the game logic
    // Parameterized constructor for Card
    Card(char value) {
        this->value = value;
        this->faceUp = false;
    }
};

class MemoryGame {
private:
    Card* cards[4][4];
    static int totalCards;  // Static variable for tracking total cards

    void initializeCards() {
        char initialCards[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                               'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

public:
    // Mutator for flipping a card
    void flipCard(int row, int col) {
        if (row >= 0 && row < 4 && col >= 0 && col < 4) {
            cards[row][col]->flip();
        }
    }

    // Accessor for total cards
    static int getTotalCards() {
        return totalCards;
    }

    // Default constructor for MemoryGame
    MemoryGame() {
        char initialCards[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                               'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

        // Shuffle the cards
        shuffleCards(initialCards, 16);

        int index = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                cards[i][j] = new Card(initialCards[index++]); // Delegating card-specific logic to Card class.
                totalCards++;
                cards[i][j] = new Card(initialCards[index++]);
                totalCards++;  // Increment total cards when a new card is created
            }
        }
    }

    // Shuffle function for card array
    void shuffleCards(char arr[], int size) {
        // Seed the random number generator
        random_device rd;
        mt19937 g(rd());

        // Shuffle the array
        shuffle(arr, arr + size, g);
    }

public:
    MemoryGame() {
        initializeCards(); // Game initialization logic is distinct from card-specific behavior.
    }

    ~MemoryGame() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                delete cards[i][j];
            }
        }
    }

    void flipCard(int row, int col) {
        if (row >= 0 && row < 4 && col >= 0 && col < 4) {
            cards[row][col]->flip(); // Uses Card class functionality for flipping.
        }
    }

    void flipAllCards() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (!cards[i][j]->isFaceUp()) {
                    cards[i][j]->flip(); // Again relies on Card for flip behavior.
                }
            }
        }
    }

    void displayCards() const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (cards[i][j]->isFaceUp()) {
                    cout << cards[i][j]->getValue() << " ";
                } else {
                    cout << "* ";
                }
            }
            cout << endl;
        }
    }

    static int getTotalCards() {
        return totalCards;
    }
};

int MemoryGame::totalCards = 0;  // Initialize static variable

int main() {
    MemoryGame game;
    int row, col;

    cout << "Initial state of the game (all cards face down):" << endl;
    game.displayCards();

    // Let the user input card positions to flip
    while (true) {
        cout << "\nEnter the row and column of the card to flip (0-3 for both) or (-1 -1) to exit: ";
        cin >> row >> col;

        if (choice == 's') {
            cout << "Enter the row and column of the card to flip (0-3 for both): ";
            cin >> row >> col;
            game.flipCard(row, col);
        } else if (choice == 'a') {
            game.flipAllCards();

        if (row == -1 && col == -1) {
            break;  // Exit loop if user inputs -1 -1

        }

        game.flipCard(row, col);
        game.displayCards();

        cout << "Remaining flips: " << GameObject::getRemainingFlips() << endl;
    }

    cout << "\nTotal cards: " << MemoryGame::getTotalCards() << endl;
    cout << "Total remaining flips: " << GameObject::getRemainingFlips() << endl;

    return 0;
}
