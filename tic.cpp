/**
 * Tic-Tac-Toe Game
 * ================
 * 
 * A classic two-player console-based Tic-Tac-Toe game.
 * 
 * Features:
 * ---------
 * - Two-player gameplay (X and O)
 * - Input validation
 * - Win detection (rows, columns, diagonals)
 * - Tie detection
 * - Play again option
 * - Color-coded output
 * - Move history tracking
 * 
 * Rules:
 * ------
 * - Players take turns placing their mark (X or O)
 * - First player to get 3 marks in a row wins
 * - Game can be played on a 3x3 grid
 */

#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>

using namespace std;

// Game constants
const int SIZE = 3;
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

// Game state
char board[SIZE][SIZE];
char currentPlayer;
int moveCount;
vector<int> moveHistory;

/**
 * Initialize the game board with numbers 1-9
 */
void initializeBoard()
{
    char num = '1';
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = num++;
        }
    }
    currentPlayer = PLAYER_X;
    moveCount = 0;
    moveHistory.clear();
}

/**
 * Display the game board with formatting
 */
void displayBoard()
{
    cout << "\n╔═══════════════╗" << endl;
    cout << "║  TIC-TAC-TOE  ║" << endl;
    cout << "╚═══════════════╝" << endl;
    cout << "\n";

    for (int i = 0; i < SIZE; i++)
    {
        cout << "     ";
        for (int j = 0; j < SIZE; j++)
        {
            // Color code the marks
            if (board[i][j] == PLAYER_X)
            {
                cout << " \033[1;34m" << board[i][j] << "\033[0m "; // Blue X
            }
            else if (board[i][j] == PLAYER_O)
            {
                cout << " \033[1;31m" << board[i][j] << "\033[0m "; // Red O
            }
            else
            {
                cout << " " << board[i][j] << " ";
            }

            if (j < SIZE - 1)
                cout << "│";
        }
        cout << "\n";

        if (i < SIZE - 1)
            cout << "     ───┼───┼───\n";
    }
    cout << "\n";
}

/**
 * Display game instructions
 */
void displayInstructions()
{
    cout << "\n╔════════════════════════════════════╗" << endl;
    cout << "║       GAME INSTRUCTIONS           ║" << endl;
    cout << "╠════════════════════════════════════╣" << endl;
    cout << "║ Enter a number (1-9) to place     ║" << endl;
    cout << "║ your mark on the board.           ║" << endl;
    cout << "║                                    ║" << endl;
    cout << "║ Board positions:                   ║" << endl;
    cout << "║     1 │ 2 │ 3                     ║" << endl;
    cout << "║    ───┼───┼───                    ║" << endl;
    cout << "║     4 │ 5 │ 6                     ║" << endl;
    cout << "║    ───┼───┼───                    ║" << endl;
    cout << "║     7 │ 8 │ 9                     ║" << endl;
    cout << "╚════════════════════════════════════╝" << endl;
}

/**
 * Check if the move is valid
 * @param move Position to check (1-9)
 * @return true if valid, false otherwise
 */
bool isValidMove(int move)
{
    if (move < 1 || move > 9)
        return false;

    int row = (move - 1) / SIZE;
    int col = (move - 1) % SIZE;

    return board[row][col] != PLAYER_X && board[row][col] != PLAYER_O;
}

/**
 * Make a move on the board
 * @param move Position to place the mark (1-9)
 */
void makeMove(int move)
{
    int row = (move - 1) / SIZE;
    int col = (move - 1) % SIZE;
    board[row][col] = currentPlayer;
    moveHistory.push_back(move);
    moveCount++;
}

/**
 * Check if current player has won
 * @return true if current player won, false otherwise
 */
bool checkWin()
{
    // Check rows and columns
    for (int i = 0; i < SIZE; i++)
    {
        // Check row
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
        {
            return true;
        }

        // Check column
        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
        {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
    {
        return true;
    }

    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
    {
        return true;
    }

    return false;
}

/**
 * Check if the game is a tie
 * @return true if all positions filled, false otherwise
 */
bool checkTie()
{
    return moveCount >= 9;
}

/**
 * Switch to the other player
 */
void switchPlayer()
{
    currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

/**
 * Clear input buffer for error handling
 */
void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * Display game statistics
 */
void displayGameStats()
{
    cout << "\n╔════════════════════════════════════╗" << endl;
    cout << "║       GAME STATISTICS             ║" << endl;
    cout << "╚════════════════════════════════════╝" << endl;
    cout << "Total moves: " << moveCount << endl;
    cout << "Move history: ";
    for (size_t i = 0; i < moveHistory.size(); i++)
    {
        cout << moveHistory[i];
        if (i < moveHistory.size() - 1)
            cout << " → ";
    }
    cout << "\n\n";
}

/**
 * Main game loop
 */
void playGame()
{
    int move;
    bool gameWon = false;

    initializeBoard();
    displayBoard();

    while (!gameWon && !checkTie())
    {
        cout << "Player \033[1m" << currentPlayer << "\033[0m, enter your move (1-9): ";
        cin >> move;

        // Handle invalid input
        if (cin.fail())
        {
            clearInputBuffer();
            cout << "\n❌ Invalid input! Please enter a number between 1 and 9.\n" << endl;
            continue;
        }

        if (isValidMove(move))
        {
            makeMove(move);
            displayBoard();

            if (checkWin())
            {
                cout << "🎉 \033[1;32mCongratulations! Player " << currentPlayer << " wins!\033[0m 🎉\n"
                     << endl;
                gameWon = true;
                displayGameStats();
            }
            else if (checkTie())
            {
                cout << "🤝 \033[1;33mIt's a tie! Well played!\033[0m 🤝\n"
                     << endl;
                displayGameStats();
            }
            else
            {
                switchPlayer();
            }
        }
        else
        {
            cout << "\n❌ Invalid move! Position already taken or out of range. Try again.\n"
                 << endl;
        }
    }
}

/**
 * Main function
 */
int main()
{
    char playAgain;

    cout << "\n╔════════════════════════════════════╗" << endl;
    cout << "║                                    ║" << endl;
    cout << "║     WELCOME TO TIC-TAC-TOE! 🎮    ║" << endl;
    cout << "║                                    ║" << endl;
    cout << "╚════════════════════════════════════╝" << endl;

    displayInstructions();

    do
    {
        playGame();

        cout << "Would you like to play again? (y/n): ";
        cin >> playAgain;
        clearInputBuffer();

        playAgain = tolower(playAgain);

    } while (playAgain == 'y');

    cout << "\n👋 Thanks for playing Tic-Tac-Toe! Goodbye!\n" << endl;

    return 0;
}
