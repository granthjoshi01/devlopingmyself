#include <iostream>
using namespace std;

const int SIZE = 3; 
char board[SIZE][SIZE] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
char currentPlayer = 'X';


void displayBoard() {
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << " " << board[i][j] << " ";
            if (j < SIZE - 1) cout << "|";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---|---|---\n";
    }
    cout << "\n";
}


bool isValidMove(int move) {
    if (move < 1 || move > 9) return false;
    int row = (move - 1) / SIZE;
    int col = (move - 1) % SIZE;
    return board[row][col] != 'X' && board[row][col] != 'O';
}



void makeMove(int move) {
    int row = (move - 1) / SIZE;
    int col = (move - 1) % SIZE;
    board[row][col] = currentPlayer;
}


bool checkWin() {
    
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) return true;
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) return true;
    }
    
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) return true;
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) return true;
    return false;
}


bool checkTie() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') return false;
        }
    }
    return true;
}


void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}


int main() {
   int move;
    bool gameWon = false;

    cout << "Welcome to Tic-Tac-Toe!\n";
    displayBoard();
 
    while (!gameWon && !checkTie()) {
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        cin >> move;

        if (isValidMove(move)) {
            makeMove(move);
            displayBoard();

            if (checkWin()) {
                cout << "Player " << currentPlayer << " wins!\n";
                gameWon = true;
            } else if (checkTie()) {
                cout << "It's a tie!\n";
            } else {
                switchPlayer();
            }
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }

    return 0;
}