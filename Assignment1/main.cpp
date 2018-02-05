#include "main.h"

int* createNewBoard(int* old_board) {
    static int new_board [ARR_SIZE] = {};
    //static int moves_available [];

    for (int i = 0; i < ARR_SIZE; i++) {
        if (old_board[i] == 2) {
            int row = i / WIDTH;
            int col = i % WIDTH;

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

int main() {

    std::cout << depthFirstSearch() << std::endl;

	system("PAUSE");

    return 1;
}