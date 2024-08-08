#include "TicTacToe.h"

TicTacToe::TicTacToe() {
    board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
    playerTurn = 'X';
}

void TicTacToe::intro() {
    char input;
    std::cout << "Do you wish to challenge Billy Ray Cyrus in Tic-Tac-Toe?\n\n";
    while (true) {
        std::cout << "--Double Tap Enter for a quick guide...";
        input = std::cin.get(); //unfortunately using looped cin.get/cin.ignore because game completely bugs out if i press the wrong key with a basic getuserinput
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (input == '\n') {
            break; 
        } else {
            std::cout << "\n\nError: I said press ENTER twice\n";
        }
     }
    std::cout << "\n";
    std::cout << " 7 | 8 | 9 \n";
    std::cout << "---+---+---\n";
    std::cout << " 4 | 5 | 6 \n";
    std::cout << "---+---+---\n";
    std::cout << " 1 | 2 | 3 \n";
    std::cout << "\nThis is the input required to mark each box, i.e. the number pad if you have one; If you do, turn on Num Lock!\n";
    std::cout << "Tread carefully...Cyrus is waiting... \n\n";
     while (true) {
        std::cout << "--Double Tap Enter to start the game...";
        input = std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //std::cin.ignore is annoying and makes me tap enter twice to clear/check input
        if (input == '\n') {
            break;
        } else {
            std::cout << "\n\nError: Please Press Enter Two Times.\n\n";
        }
     }
}

void TicTacToe::play() {
    std::srand(std::time(nullptr));
    std::vector<char> availablePositions = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    while (true) {
    printBoard();
    if (playerTurn == 'X') {
        int position;
        std::cout << "--You are X's - Enter a position (1-9): ";
        std::cin >> position;
        std::cout << "\n";
        try {
            if (position < 1 || position > 9 || availablePositions[position - 1] != position + '0') {
                throw InvalidMoveException(); // Custom exception
            }
            int row = (position - 1) / 3;
            int col = (position - 1) % 3;
            if (board[row][col] != ' ') {
                throw InvalidMoveException(); // Spot already taken
            }
            board[row][col] = 'X';
            availablePositions[position - 1] = 'X';
        } catch (const InvalidMoveException& e) {
            std::cerr << e.what() << "\nYour move has to be a number 1-9, and you gotta pick an open spot \n" << std::endl; //already returns output in header file whoops
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            continue;
            }
        } 
        else {
            computerMove();
        }
        if (checkWin('X')) {
            printBoard();
            std::cout << "\n Congrats man, you got me this time\n" << std::endl;
            break;
        } else if (checkWin('O')) {
            printBoard();
            std::cout << "\n Can't even beat me on an off day, c'mon man\n" << std::endl;
            break;
        } else if (checkTie()) {
            printBoard();
            std::cout << "\n We call this a Cat's game in Kentucky\n" << std::endl;
            break;
        }
        playerTurn = (playerTurn == 'X') ? 'O' : 'X';
    }
}



void TicTacToe::printBoard() {
    std::cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " \n";
    std::cout << "---+---+---\n";
    std::cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " \n";
    std::cout << "---+---+---\n";
    std::cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " \n";
     std::cout << "\n";
}

bool TicTacToe::checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    return false;
}

bool TicTacToe::checkTie() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true; 
}

void TicTacToe::computerMove() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                if (checkWin('O')) {
                    return;
                }
                board[i][j] = ' '; 
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                if (checkWin('X')) {
                    board[i][j] = 'O';
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    if (board[1][1] == ' ') {
        board[1][1] = 'O';
        return;
    }

    const int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (const auto& corner : corners) {
        int row = corner[0];
        int col = corner[1];
        if (board[row][col] == ' ') {
            board[row][col] = 'O';
            return;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                return;
            }
        }
    }
}