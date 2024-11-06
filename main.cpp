#include <iostream> 
#include <algorithm>  // For std::shuffle
#include <random>     // For std::random_device and std::mt19937
#include <ctime>      // For seeding the random number generator

using namespace std;

class Card {
private:
    char value;
    bool faceUp;
    static int flipCount;

public:
    char getValue() const {
        return value;
    }

    void flip() {
        faceUp = !faceUp;
        flipCount++;
    }

    bool isFaceUp() const {
        return faceUp;
    }

    static int getFlipCount() {
        return flipCount;
    }

    Card(char value) {
        this->value = value;
        this->faceUp = false;
    }
};

int Card::flipCount = 0;

class MemoryGame {
private:
    Card* cards[4][4];
    static int totalCards;

public:
    void flipCard(int row, int col) {  // Function overloading: specific card flip
        if (row >= 0 && row < 4 && col >= 0 && col < 4) {
            cards[row][col]->flip();
        }
    }

    void flipCard() {  // Function overloading: flip all cards
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (!cards[i][j]->isFaceUp()) {
                    cards[i][j]->flip();
                }
            }
        }
    }

    static int getTotalCards() {
        return totalCards;
    }

    MemoryGame() {
        char initialCards[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                               'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

        shuffleCards(initialCards, 16);

        int index = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                cards[i][j] = new Card(initialCards[index++]);
                totalCards++;
            }
        }
    }

    void shuffleCards(char arr[], int size) {
        random_device rd;
        mt19937 g(rd());
        shuffle(arr, arr + size, g);
    }

    ~MemoryGame() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                delete cards[i][j];
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
            game.flipCard(row, col);  // Calls specific card flip (overloaded function)
        } else if (choice == 'a') {
            game.flipCard();  // Calls all-cards flip (overloaded function)
        }

        game.displayCards();
    }

    cout << "\nTotal cards: " << MemoryGame::getTotalCards() << endl;
    cout << "Total flips: " << Card::getFlipCount() << endl;

    return 0;
}
