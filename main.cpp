#include <iostream>

using namespace std;

class Card {
private:
    char value;           // Private member: Only accessible within the Card class
    bool faceUp;          // Private member: Keeps track of whether the card is face-up
    static int flipCount; // Private static member: Tracks how many times cards have been flipped

public:
    // Accessor for card value (public)
    char getValue() const {
        return value;  // Returns the card's value
    }

    // Mutator for flipping the card (public)
    void flip() {
        faceUp = !faceUp;  // Toggles the card's face-up state
        flipCount++;       // Increments the global flip count
    }

    // Accessor for faceUp state (public)
    bool isFaceUp() const {
        return faceUp;  // Returns true if the card is face-up
    }

    // Static accessor for flip count (public)
    static int getFlipCount() {
        return flipCount;  // Returns the total number of card flips
    }

    // Constructor (public) initializes card value and sets faceUp to false
    Card(char value) {
        this->value = value;
        this->faceUp = false;
    }
};

// Initialize static variable outside the class
int Card::flipCount = 0;

class MemoryGame {
private:
    Card* cards[4][4];    // Private member: Only accessible within the MemoryGame class
    static int totalCards;// Private static member: Tracks the total number of cards in the game

public:
    // Mutator for flipping a card (public)
    void flipCard(int row, int col) {
        if (row >= 0 && row < 4 && col >= 0 && col < 4) {
            cards[row][col]->flip();  // Flips the card at the given row and column
        }
    }

    // Accessor for total cards (public)
    static int getTotalCards() {
        return totalCards;  // Returns the total number of cards in the game
    }

    // Constructor (public) that initializes the cards in the game
    MemoryGame() {
        char initialCards[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                               'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
        int index = 0;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                cards[i][j] = new Card(initialCards[index++]);  // Dynamically allocate memory for each card
                totalCards++;  // Increment the total number of cards
            }
        }
    }

    ~MemoryGame() {
        // Destructor (public) to release dynamically allocated memory
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                delete cards[i][j];  // Free the memory for each card
            }
        }
    }

    // Public member function to display the game board
    void displayCards() const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (cards[i][j]->isFaceUp()) {  // Checks if the card is face-up
                    cout << cards[i][j]->getValue() << " ";  // Displays the card's value if it's face-up
                } else {
                    cout << "* ";  // Otherwise, display a placeholder
                }
            }
            cout << endl;
        }
    }
};

// Initialize static variable outside the class
int MemoryGame::totalCards = 0;

int main() {
    MemoryGame game;
    int row, col;

    cout << "Initial state of the game (all cards face down):" << endl;
    game.displayCards();

    // Let the user input card positions to flip
    while (true) {
        cout << "\nEnter the row and column of the card to flip (0-3 for both) or (-1 -1) to exit: ";
        cin >> row >> col;

        if (row == -1 && col == -1) {
            break;  // Exit loop if user inputs -1 -1
        }

        game.flipCard(row, col);
        game.displayCards();
    }

    cout << "\nTotal cards: " << MemoryGame::getTotalCards() << endl;
    cout << "Total flips: " << Card::getFlipCount() << endl;

    return 0;
}
