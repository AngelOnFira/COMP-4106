#include "main.h"

int* createNewBoard(int* old_board) {
    static int new_board [49] = {};

    for (int i = 0; i < 49; i++) {
        if (old_board[i] == 2) {
            int row = i / 7;
            int col = i % 7;

            if (row >= 2) {
                if (old_board[i - 14] == 1) {
                    new_board[i - 14] = 1;
                }
            }
            if (row <= 4) {
                if (old_board[i + 14] == 1) {
                    new_board[i + 14] = 1;
                }
            }
            if (col >= 2) {
                if (old_board[i - 2] == 1) {
                    new_board[i - 2] = 1;
                }
            }
            if (col <= 4) {
                if (old_board[i + 2] == 1) {
                    new_board[i + 2] = 1;
                }
            }
        }
    }
    return new_board;
}

void printBoard(int* board) {
    for (int y = 0; y < 7; y++) {
        for (int x = 0; x < 7; x++) {
            int pos = y * 7 + x;
            if (board[pos] == 0 || board[pos] == 2) {
                std::cout << "[0]";
            }
            else {
                std::cout << "[1]";
            }
        }
        std::cout << "" << std::endl;
    }
}

int main() {
    int board [49] = {
        0, 0, 1, 1, 1, 0, 0,
        0, 1, 1, 1, 1, 1, 0,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 2, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 0,
        0, 0, 1, 1, 1, 0, 0,
    };

    int* new_board = createNewBoard(board);

    printBoard(new_board);

    return 1;
}