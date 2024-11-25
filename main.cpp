#include <iostream>
#include <algorithm>  // For std::shuffle
#include <random>     // For std::random_device and std::mt19937
#include <ctime>      // For seeding the random number generator
#include <thread>     // For sleep
#include <chrono>     // For sleep duration

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
    int score;
    int remainingFlips;

public:
    MemoryGame() : score(0), remainingFlips(30) {
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

    void unflipCards(Card* card1, Card* card2) {
        this_thread::sleep_for(chrono::seconds(1));  // Pause for 1 second
        card1->flip();
        card2->flip();
    }

    void flipSpecificCard(int row1, int col1, int row2, int col2) {
        if (row1 < 0 || row1 >= 4 || col1 < 0 || col1 >= 4 ||
            row2 < 0 || row2 >= 4 || col2 < 0 || col2 >= 4 ||
            remainingFlips <= 0) {
            cout << "Invalid input or no flips remaining!\n";
            return;
        }

        if (row1 == row2 && col1 == col2) {
            cout << "You cannot select the same card twice!\n";
            return;
        }

        if (!cards[row1][col1]->isFaceUp() && !cards[row2][col2]->isFaceUp()) {
            cards[row1][col1]->flip();
            cards[row2][col2]->flip();
            remainingFlips--;

            displayCards();

            if (cards[row1][col1]->getValue() == cards[row2][col2]->getValue()) {
                cout << "Match found! +1 point\n";
                score++;
            } else {
                cout << "No match. Cards will be flipped back.\n";
                unflipCards(cards[row1][col1], cards[row2][col2]);
            }

            cout << "Score: " << score << " | Remaining flips: " << remainingFlips << "\n";
        } else {
            cout << "One or both cards are already face up!\n";
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

    int getScore() const {
        return score;
    }

    int getRemainingFlips() const {
        return remainingFlips;
    }

    ~MemoryGame() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                delete cards[i][j];
            }
        }
    }
};

int MemoryGame::totalCards = 0;

int main() {
    MemoryGame game;
    int row1, col1, row2, col2;

    cout << "Initial state of the game (all cards face down):" << endl;
    game.displayCards();

    while (game.getRemainingFlips() > 0) {
        cout << "\nEnter the coordinates of the first card to flip (row and column, 0-3): ";
        cin >> row1 >> col1;

        cout << "Enter the coordinates of the second card to flip (row and column, 0-3): ";
        cin >> row2 >> col2;

        game.flipSpecificCard(row1, col1, row2, col2);

        if (game.getScore() == 8) {  // All matches found
            cout << "\nCongratulations! You've matched all the cards.\n";
            break;
        }
    }

    if (game.getRemainingFlips() == 0 && game.getScore() < 8) {
        cout << "\nGame Over! Final score: " << game.getScore() << "\n";
    }

    return 0;
}
