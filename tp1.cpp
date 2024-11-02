#include<iostream>

#include<iostream>
#include<vector>

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;

public:
    TicTacToe() : board(3, std::vector<char>(3, ' ')), currentPlayer('X') {}

    void printBoard() {
        for (auto &row : board) {
            for (char cell : row) {
                std::cout << (cell == ' ' ? '-' : cell) << ' ';
            }
            std::cout << std::endl;
        }
    }

    bool makeMove(int row, int col) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            return false;
        }
        board[row][col] = currentPlayer;
        return true;
    }

    bool checkWin() {
        // Check rows and columns
        for (int i = 0; i < 3; ++i) {
            if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
                (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
                return true;
            }
        }
        // Check diagonals
        if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
            (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
            return true;
        }
        return false;
    }

    bool isDraw() {
        for (auto &row : board) {
            for (char cell : row) {
                if (cell == ' ') return false;
            }
        }
        return true;
    }

    void changePlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    char getCurrentPlayer() {
        return currentPlayer;
    }
};

int main() {
    TicTacToe game;
    int row, col;
    while (true) {
        game.printBoard();
        std::cout << "Player " << game.getCurrentPlayer() << ", enter your move (row and column): ";
        std::cin >> row >> col;
        
        if (!game.makeMove(row, col)) {
            std::cout << "Invalid move. Try again." << std::endl;
            continue;
        }

        if (game.checkWin()) {
            game.printBoard();
            std::cout << "Player " << game.getCurrentPlayer() << " wins!" << std::endl;
            break;
        }

        if (game.isDraw()) {
            game.printBoard();
            std::cout << "The game is a draw!" << std::endl;
            break;
        }

        game.changePlayer();
    }
    return 0;
}
