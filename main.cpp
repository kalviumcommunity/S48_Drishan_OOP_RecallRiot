#include <iostream>  
#include <algorithm>  // For std::shuffle
#include <random>     // For std::random_device and std::mt19937
#include <ctime>      // For seeding the random number generator

using namespace std;

// Class handling card-specific details
class Card {
private:
    char value;
    bool faceUp;
    static int flipCount;

public:
    Card(char value) : value(value), faceUp(false) {} // Card handles only its state and behavior.

    char getValue() const {
        return value;
    }

    void flip() {
        faceUp = !faceUp; // Flipping logic specific to the card.
        flipCount++;
    }

    bool isFaceUp() const {
        return faceUp;
    }

    static int getFlipCount() {
        return flipCount;
    }
};

int Card::flipCount = 0;

// Class managing the game logic
class MemoryGame {
private:
    Card* cards[4][4];
    static int totalCards;

    void initializeCards() {
        char initialCards[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                               'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
        shuffleCards(initialCards, 16);

        int index = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                cards[i][j] = new Card(initialCards[index++]); // Delegating card-specific logic to Card class.
                totalCards++;
            }
        }
    }

    void shuffleCards(char arr[], int size) {
        random_device rd;
        mt19937 g(rd());
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

int MemoryGame::totalCards = 0;

int main() {
    MemoryGame game;
    int row, col;
    char choice;

    cout << "Initial state of the game (all cards face down):" << endl;
    game.displayCards();

    while (true) {
        cout << "\nEnter 's' to flip a specific card, 'a' to flip all cards, or 'q' to quit: ";
        cin >> choice;

        if (choice == 'q') {
            break;
        }

        if (choice == 's') {
            cout << "Enter the row and column of the card to flip (0-3 for both): ";
            cin >> row >> col;
            game.flipCard(row, col);
        } else if (choice == 'a') {
            game.flipAllCards();
        }

        game.displayCards();
    }

    cout << "\nTotal cards: " << MemoryGame::getTotalCards() << endl;
    cout << "Total flips: " << Card::getFlipCount() << endl;

    return 0;
}
