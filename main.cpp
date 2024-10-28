#include <iostream>
#include <algorithm>  // For std::shuffle
#include <random>     // For std::random_device and std::mt19937

using namespace std;

// Base class for Cards
class Card {
protected:
    char value;
    bool faceUp;
    static int flipCount;

public:
    // Accessor for card value
    char getValue() const {
        return value;
    }

    // Mutator for flipping the card
    void flip() {
        faceUp = !faceUp;
        if (flipCount > 0) {
            flipCount--;  // Decrement flip count on each flip
        }
    }

    // Accessor for faceUp state
    bool isFaceUp() const {
        return faceUp;
    }

    // Static accessor for flip count
    static int getFlipCount() {
        return flipCount;
    }

    // Parameterized constructor for Card
    Card(char value) {
        this->value = value;
        this->faceUp = false;
    }
};

int Card::flipCount = 30; // Initialize flipCount to 30

// Derived class for SpecialCard (Single Inheritance)
class SpecialCard : public Card {
private:
    bool specialAbility;

public:
    SpecialCard(char value, bool ability) : Card(value), specialAbility(ability) {}

    // New function to check if the card has a special ability
    bool hasSpecialAbility() const {
        return specialAbility;
    }
};

// Another class for the game board (Multilevel Inheritance)
class GameBoard {
protected:
    SpecialCard* board[4][4];
public:
    virtual void displayBoard() const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (board[i][j]->isFaceUp()) {
                    cout << board[i][j]->getValue() << " ";
                } else {
                    cout << "* ";
                }
            }
            cout << endl;
        }
    }
};

// MemoryGame now inherits from GameBoard (Multilevel Inheritance)
class MemoryGame : public GameBoard {
private:
    static int totalCards;

public:
    // Constructor for MemoryGame
    MemoryGame() {
        char initialCards[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                               'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

        shuffleCards(initialCards, 16);

        int index = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                board[i][j] = new SpecialCard(initialCards[index++], false);
                totalCards++;
            }
        }
    }

    // Shuffle function for cards
    void shuffleCards(char arr[], int size) {
        random_device rd;
        mt19937 g(rd());
        shuffle(arr, arr + size, g);
    }

    // Destructor for MemoryGame
    ~MemoryGame() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                delete board[i][j];
            }
        }
    }

    // Flip a card on the board
    void flipCard(int row, int col) {
        if (row >= 0 && row < 4 && col >= 0 && col < 4) {
            board[row][col]->flip();
        }
    }

    // Accessor for total cards
    static int getTotalCards() {
        return totalCards;
    }

    // Check if the game is over (when flipCount is 0)
    bool isGameOver() const {
        return Card::getFlipCount() == 0;
    }
};

int MemoryGame::totalCards = 0;

int main() {
    MemoryGame game;
    int row, col;

    cout << "Initial state of the game (all cards face down):" << endl;
    game.displayBoard();

    while (true) {
        if (game.isGameOver()) {
            cout << "\nGame Over! No more flips remaining." << endl;
            break;
        }

        cout << "\nRemaining flips: " << Card::getFlipCount() << endl;
        cout << "Enter the row and column of the card to flip (0-3 for both) or (-1 -1) to exit: ";
        cin >> row >> col;

        if (row == -1 && col == -1) {
            break;  // Exit loop if user inputs -1 -1
        }

        game.flipCard(row, col);
        game.displayBoard();
    }

    cout << "\nTotal cards: " << MemoryGame::getTotalCards() << endl;
    cout << "Total flips: " << Card::getFlipCount() << endl;

    return 0;
}
