#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <ctime>

class TicTacToe {
public:
    TicTacToe();
    void intro();
    void play();
    void printBoard();
    bool checkWin(char player);
    bool checkTie();
    void computerMove();

private:
    std::vector<std::vector<char>> board;
    char playerTurn;
};

class InvalidMoveException : public std::exception {
public:
    const char* what() const throw() {
        return "\nYou never play Tic-Tac-Toe before?";
    }
};

#endif
