#include <iostream>
#include <vector>
#include <limits>
#include <SFML/Graphics.hpp>
class TicTacToe {
private:
    char currentPlayer;

    int minimax(bool isMaximizing) {
        if (checkWin()) {
            return isMaximizing ? -1 : 1;
        }
        if (isDraw()) {
            return 0;
        }

        int bestScore = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = isMaximizing ? 'O' : 'X';
                    int score = minimax(!isMaximizing);
                    board[i][j] = ' ';
                    bestScore = isMaximizing ? std::max(score, bestScore) : std::min(score, bestScore);
                }
            }
        }
        return bestScore;
    }

    int getBestMove() {
        int bestScore = std::numeric_limits<int>::min();
        int move = -1;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(false);
                    board[i][j] = ' ';
                    if (score > bestScore) {
                        bestScore = score;
                        move = i * 3 + j + 1;
                    }
                }
            }
        }
        return move;
    }

public:
    std::vector<std::vector<char>> board;

    TicTacToe() : board(3, std::vector<char>(3, ' ')), currentPlayer('X') {}

    void printBoard() {
        for (int i = 0; i < 3; ++i) {
            std::cout << i * 3 + 1 << ' ' << i * 3 + 2 << ' ' << i * 3 + 3 << std::endl;
            for (char cell : board[i]) {
                std::cout << (cell == ' ' ? '-' : cell) << ' ';
            }
            std::cout << std::endl;
        }
    }

    bool makeMove(int move) {
        if (move < 1 || move > 9) {
            return false;
        }
        int row = (move - 1) / 3;
        int col = (move - 1) % 3;
        if (board[row][col] != ' ') {
            return false;
        }
        board[row][col] = currentPlayer;
        return true;
    }

    bool checkWin() {
        for (int i = 0; i < 3; ++i) {
            if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
                (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
                return true;
            }
        }
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

    void playBestMove() {
        if (currentPlayer == 'O') {
            int bestMove = getBestMove();
            makeMove(bestMove);
        }
    }
};



int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 300), "Tic Tac Toe");
    TicTacToe game;

    sf::Font font;
    if (!font.loadFromFile("Monocraft.ttf"))  
        return -1;

    sf::Text text("", font, 24);
    text.setFillColor(sf::Color::Black);

    sf::RectangleShape shape(sf::Vector2f(100, 100));
    shape.setFillColor(sf::Color(255, 255, 255));
    shape.setOutlineColor(sf::Color(0, 0, 0));
    shape.setOutlineThickness(2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int x = event.mouseButton.x / 100;
                int y = event.mouseButton.y / 100;
                int move = y * 3 + x + 1;

                
                if (game.board[y][x] == ' ' && game.makeMove(move))
                {
                    if (game.checkWin())
                    {
                        text.setString("Player " + std::string(1, game.getCurrentPlayer()) + " wins!");
                        text.setPosition(50, 250);
                        window.draw(text);
                        window.display();
                        sf::sleep(sf::seconds(3)); 
                        window.close();
                    }
                    game.changePlayer();
                }
            }
        }

        window.clear();
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                shape.setPosition(i * 100, j * 100);
                window.draw(shape);
                
                
                if (game.board[j][i] == 'X')
                {
                    text.setString("X");
                    text.setPosition(i * 100 + 40, j * 100 + 20);
                    window.draw(text);
                }
                else if (game.board[j][i] == 'O')
                {
                    text.setString("O");
                    text.setPosition(i * 100 + 40, j * 100 + 20);
                    window.draw(text);
                }
            }
        }

        
        if (game.isDraw())
        {
            text.setString("It's a draw!");
            text.setPosition(50, 250);
            window.draw(text);
            window.display();
            sf::sleep(sf::seconds(3)); 
            window.close();
        }

        window.display();
    }

    return 0;
}

