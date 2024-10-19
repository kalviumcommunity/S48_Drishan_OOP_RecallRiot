#include <iostream>

using namespace std;

class Card {
private:
    char value;
    bool faceUp;
    static int flipCount;

public:

    // Constructor using 'this'
    Card(char value) {
        this->value = value;
        this->faceUp = false;
    }

    // Accessor for card value
    char getValue() const {
        return value;
    }

    // Mutator for flipping the card
    void flip() {
        faceUp = !faceUp;
        flipCount++;
    }

    // Accessor for faceUp state
    bool isFaceUp() const {
        return faceUp;
    }

    // Static accessor for flip count
    static int getFlipCount() {
        return flipCount;
    }

};

int Card::flipCount = 0;

class MemoryGame {
private:
    Card* cards[4][4];
    static int totalCards;

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

    MemoryGame() {
        char initialCards[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                               'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
        int index = 0;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                cards[i][j] = new Card(initialCards[index++]);
                totalCards++;
            }
        }
    }

    ~MemoryGame() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                delete cards[i][j];
            }
        }
    }

    // Accessor for displaying cards
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
};

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
