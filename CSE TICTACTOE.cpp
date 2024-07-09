#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class TicTacToe {
private:
    char board[3][3][3];
    bool bEndGame;
    int userWins;
    int computerWins;

public:
    TicTacToe() {
        resetBoard();
        bEndGame = false;
        userWins = 0;
        computerWins = 0;
    }

    void resetBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    board[i][j][k] = ' ';
                }
            }
        }
    }

    void TicTacToeUi() {
        system("cls");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cout << " " << board[i][j][k];
                    if (k < 2) cout << " | ";
                }
                cout << endl;
                if (j < 2) cout << "-------------" << endl;
            }
            cout << endl;
        }
        cout << "User Wins: " << userWins << endl;
        cout << "Computer Wins: " << computerWins << endl;
    }

    void UserChoice() {
        int iLayer, iColumn, iRow;
        cout << "Enter which layer, row, then column where you want to place your X!" << endl;
        cin >> iLayer >> iColumn >> iRow;
        --iLayer;
        --iColumn;
        --iRow;

        if (iLayer >= 0 && iLayer < 3 && iColumn >= 0 && iColumn < 3 && iRow >= 0 && iRow < 3 && board[iLayer][iColumn][iRow] == ' ') {
            board[iLayer][iColumn][iRow] = 'X';
        } else {
            cout << "Spot has been filled already, select a different spot" << endl;
            UserChoice();
        }
    }

    void ComputerChoice() {
        int iLayer, iColumn, iRow;
        iLayer = rand() % 3;
        iColumn = rand() % 3;
        iRow = rand() % 3;

        if (board[iLayer][iColumn][iRow] == ' ') {
            board[iLayer][iColumn][iRow] = 'O';
        } else {
            ComputerChoice();
        }
    }

    bool checkWin(char player) {
        // Check for a win in rows, columns, diagonals, and layers
        for (int i = 0; i < 3; ++i) {
            // Check rows
            for (int j = 0; j < 3; ++j) {
                if (board[i][j][0] == player && board[i][j][1] == player && board[i][j][2] == player)
                    return true;
            }
            // Check columns
            for (int k = 0; k < 3; ++k) {
                if (board[i][0][k] == player && board[i][1][k] == player && board[i][2][k] == player)
                    return true;
            }
            // Check diagonals
            if (board[i][0][0] == player && board[i][1][1] == player && board[i][2][2] == player)
                return true;
            if (board[i][0][2] == player && board[i][1][1] == player && board[i][2][0] == player)
                return true;
        }

        // Check for wins across layers
        for (int j = 0; j < 3; ++j) {
            // Check rows
            for (int k = 0; k < 3; ++k) {
                if (board[0][j][k] == player && board[1][j][k] == player && board[2][j][k] == player)
                    return true;
            }
            // Check columns
            for (int i = 0; i < 3; ++i) {
                if (board[i][j][0] == player && board[i][j][1] == player && board[i][j][2] == player)
                    return true;
            }
        }

        // Check diagonals across layers
        for (int k = 0; k < 3; ++k) {
            if (board[0][0][k] == player && board[1][1][k] == player && board[2][2][k] == player)
                return true;
            if (board[0][2][k] == player && board[1][1][k] == player && board[2][0][k] == player)
                return true;
        }

        // Check main diagonals within the same layer
        if (board[0][0][0] == player && board[1][1][1] == player && board[2][2][2] == player)
            return true;
        if (board[0][2][2] == player && board[1][1][1] == player && board[2][0][0] == player)
            return true;

        // Check for diagonal wins through different layers
        if (board[0][0][0] == player && board[1][0][1] == player && board[2][0][2] == player)
            return true;
        if (board[0][0][2] == player && board[1][0][1] == player && board[2][0][0] == player)
            return true;
        if (board[0][2][0] == player && board[1][1][0] == player && board[2][0][0] == player)
            return true;
        if (board[0][2][2] == player && board[1][1][2] == player && board[2][0][2] == player)
            return true;
        if (board[0][0][0] == player && board[1][1][0] == player && board[2][2][0] == player)
            return true;
        if (board[0][2][0] == player && board[1][1][0] == player && board[2][0][0] == player)
            return true;

        return false;
    }

    void startGame() {
        srand(time(0));
        int moves = 0;
        char whoWon = ' ';
        bool playAgain = true;

        while (playAgain) {
            resetBoard();
            bEndGame = false;
            TicTacToeUi();
            int iRandGoFirst = rand() % 2;
            if (iRandGoFirst == 0) {
                cout << "You get to pick first!" << endl;
            } else {
                cout << "The computer will start off" << endl;
                ComputerChoice();
                TicTacToeUi();
                moves++;
            }
            while (!bEndGame) {
                UserChoice();
                TicTacToeUi();
                if (checkWin('X')) {
                    bEndGame = true;
                    whoWon = 'X';
                    userWins++;
                    break;
                }
                moves++;
                if (moves == 27) {
                    bEndGame = true;
                    cout << "It's a scratch!" << endl;
                    break;
                }
                ComputerChoice();
                TicTacToeUi();
                if (checkWin('O')) {
                    bEndGame = true;
                    whoWon = 'O';
                    computerWins++;
                    break;
                }
                moves++;
            }
            cout << "The game is over" << endl;
            if (whoWon == 'X') {
                cout << "The user has won, good job!" << endl;
            } else if (whoWon == 'O') {
                cout << "The computer has won, better luck next time!" << endl;
            }

            char playAgainChoice;
            cout << "Do you want to play again? (Y/N): ";
            cin >> playAgainChoice;
            playAgain = (playAgainChoice == 'Y' || playAgainChoice == 'y');
        }
        cout << "Thanks for playing!" << endl;
        cout << "Final Score:" << endl;
        cout << "User Wins: " << userWins << endl;
        cout << "Computer Wins: " << computerWins << endl;
    }
};

int main() {
    TicTacToe loop;
    loop.startGame();
    return 0;
}
