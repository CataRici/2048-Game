#include <iostream>
#include <ctime>
#include <cstdlib>
#include<iomanip>

const int MAX_SIZE = 4;
int board[MAX_SIZE][MAX_SIZE];
int directionLine[] = {1, 0, -1, 0}; //numbers for mapping
int directionColumn[] = {0 ,1, 0, -1}; //numbers for mapping


// Generates a random free position on the board 
std::pair<int, int> createUnoccupiedPosition() {
    int occupied = 1, line, column;
    while (occupied) {
        line = rand() % 4;
        column = rand() % 4;
        if (board[line][column] == 0) {
            occupied = 0;
        }
        return std::make_pair(line, column);
    }
}

// Add value 2 on the new position
void addValue() {
    std::pair<int, int> pos = createUnoccupiedPosition();
    board[pos.first][pos.second] = 2;
}

// Reset all board position to 0 and add a value 2 to start new game;
void newGame() {
    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int j = 0; j < MAX_SIZE; ++j) {
            board[i][j] = 0;
        }
    }
    addValue();
}

// Print the board and game commands
void printUI() {
    system("cls");
    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int j = 0; j < MAX_SIZE; ++j) {
            if (board[i][j] == 0) {
                std::cout << std::setw(4)<< "_" << " ";
            } else {
                std::cout << std::setw(4) << board[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << "n = NEW GAME, w = UP, s = DOWN, a = LEFT, d = RIGHT, q = QUIT \n";
}

// Check if the move if possible
bool canMove(int line, int column, int nextLine, int nextColumn) {
    if (nextLine < 0 || nextColumn < 0 || nextLine >= MAX_SIZE || nextColumn >= MAX_SIZE ||
        (board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0)) {
        return false;
    }
    return true;
}

// Make the move on the board and sum the values
void move(int currentDirection) {
    int startLine = 0, startColumn = 0, lineStep = 1, columnStep = 1;
    if (currentDirection == 0) {
        startLine = 3;
        lineStep = -1;
    }
    if (currentDirection == 1) {
        startColumn = 3;
        columnStep = -1;
    }
    int possibleMove = 0, canAddPiece = 0;
    do {
        possibleMove = 0;
        for (int i = startLine; i >= 0 && i < MAX_SIZE; i += lineStep) {
            for (int j = startColumn; j >= 0 && j < MAX_SIZE; j += columnStep) {
                int nextI = i + directionLine[currentDirection], nextJ = j + directionColumn[currentDirection];
                if (board[i][j] != 0 && canMove(i, j, nextI, nextJ)) {
                    board[nextI][nextJ] += board[i][j];
                    board[i][j] = 0;
                    possibleMove = canAddPiece = 1;
                    if (board[nextI][nextJ] == 32) {
                        std::cout << "ai castigat!";
                    }
                }
            }
        }
    } while (possibleMove);
    if (canAddPiece) {
        addValue();
    }
}

int main() {
    newGame();
    char directionCommand[128];
    directionCommand['s'] = 0;
    directionCommand['d'] = 1;
    directionCommand['w'] = 2;
    directionCommand['a'] = 3;
    while (true) {
        printUI();
        char command;
        std::cin >> command;
        if (command == 'n') {
            newGame();
        } else if (command == 'q') {
            break;
        } else {
            int currentDirection = directionCommand[command];
            move(currentDirection);
        }
    }
    return 0;
}

