// Name: A Chao Thao
// Below code is genereated by ChatGPT

/*
Here's a full implementation of the SOS game in C++ with a computer opponent, 
supporting both Simple and General game modes. 
For simplicity, this implementation assumes a fixed board size. 
You can adapt it to use a dynamic board size if needed.
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 5; // Define the board size
char board[SIZE][SIZE];
enum GameMode { SIMPLE, GENERAL };
GameMode gameMode;

// Function prototypes
void initializeBoard();
void displayBoard();
bool isValidMove(int x, int y);
bool isSOS(int x, int y, char symbol);
void playerMove();
void computerMoveSimple();
void computerMoveGeneral();
void randomMove();
bool isGameOver();
void switchPlayer();
int countSOS();
int currentPlayer = 0; // 0: Human, 1: Computer

int main() {
    srand(time(0)); // Seed for randomness

    cout << "Welcome to the SOS Game!" << endl;
    cout << "Select Game Mode: " << endl;
    cout << "1. Simple Game" << endl;
    cout << "2. General Game" << endl;
    int choice;
    cin >> choice;

    gameMode = (choice == 1) ? SIMPLE : GENERAL;

    initializeBoard();
    displayBoard();

    while (!isGameOver()) {
        if (currentPlayer == 0) {
            cout << "Your turn!" << endl;
            playerMove();
        } else {
            cout << "Computer's turn!" << endl;
            if (gameMode == SIMPLE) {
                computerMoveSimple();
            } else {
                computerMoveGeneral();
            }
        }
        displayBoard();
        switchPlayer();
    }

    // Determine the winner
    int humanSOS = countSOS();
    int computerSOS = countSOS();
    if (gameMode == SIMPLE) {
        if (humanSOS > 0) {
            cout << "You win!" << endl;
        } else if (computerSOS > 0) {
            cout << "Computer wins!" << endl;
        } else {
            cout << "It's a draw!" << endl;
        }
    } else { // General mode
        if (humanSOS > computerSOS) {
            cout << "You win!" << endl;
        } else if (computerSOS > humanSOS) {
            cout << "Computer wins!" << endl;
        } else {
            cout << "It's a draw!" << endl;
        }
    }

    return 0;
}

void initializeBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard() {
    cout << endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << " | ";
        }
        cout << endl;
        if (i < SIZE - 1) {
            for (int k = 0; k < SIZE; ++k) {
                cout << "---";
                if (k < SIZE - 1) cout << "+";
            }
            cout << endl;
        }
    }
    cout << endl;
}

bool isValidMove(int x, int y) {
    return (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == ' ');
}

bool isSOS(int x, int y, char symbol) {
    // Check horizontal
    if (y > 0 && y < SIZE - 1 && board[x][y - 1] == 'S' && board[x][y + 1] == 'S')
        return true;
    // Check vertical
    if (x > 0 && x < SIZE - 1 && board[x - 1][y] == 'S' && board[x + 1][y] == 'S')
        return true;
    // Check diagonals
    if (x > 0 && x < SIZE - 1 && y > 0 && y < SIZE - 1) {
        if (board[x - 1][y - 1] == 'S' && board[x + 1][y + 1] == 'S')
            return true;
        if (board[x - 1][y + 1] == 'S' && board[x + 1][y - 1] == 'S')
            return true;
    }
    return false;
}

void playerMove() {
    int x, y;
    char symbol;
    do {
        cout << "Enter row, column, and symbol (S or O): ";
        cin >> x >> y >> symbol;
    } while (!isValidMove(x, y) || (symbol != 'S' && symbol != 'O'));
    board[x][y] = symbol;
}

void computerMoveSimple() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (isValidMove(i, j)) {
                board[i][j] = 'S';
                if (isSOS(i, j, 'S')) return;
                board[i][j] = 'O';
                if (isSOS(i, j, 'O')) return;
                board[i][j] = ' ';
            }
        }
    }
    randomMove();
}

void computerMoveGeneral() {
    bool anotherTurn = true;
    while (anotherTurn) {
        anotherTurn = false;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (isValidMove(i, j)) {
                    board[i][j] = 'S';
                    if (isSOS(i, j, 'S')) {
                        anotherTurn = true;
                        return;
                    }
                    board[i][j] = 'O';
                    if (isSOS(i, j, 'O')) {
                        anotherTurn = true;
                        return;
                    }
                    board[i][j] = ' ';
                }
            }
        }
    }
    randomMove();
}

void randomMove() {
    vector<pair<int, int>> validMoves;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (isValidMove(i, j)) validMoves.push_back({i, j});
        }
    }
    if (!validMoves.empty()) {
        auto move = validMoves[rand() % validMoves.size()];
        board[move.first][move.second] = (rand() % 2 == 0) ? 'S' : 'O';
    }
}

bool isGameOver() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

void switchPlayer() {
    currentPlayer = 1 - currentPlayer;
}

int countSOS() {
    int count = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (isSOS(i, j, board[i][j])) {
                count++;
            }
        }
    }
    return count;
}