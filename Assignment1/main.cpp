#include "main.h"

#define ARR_SIZE 49
#define WIDTH 7


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

int depthFirstSearch() {
    //static int board [ARR_SIZE] = {};
    std::stack<int*> fringe;
	std::stack<std::vector<int>> breakcrumbs;
    std::unordered_map<std::string,bool> check_position;

    bool compare = true;
    int* win_board = new int[ARR_SIZE] {
        0, 0, 2, 2, 2, 0, 0,
        0, 2, 2, 2, 2, 2, 0,
        2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 1, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2,
        0, 2, 2, 2, 2, 2, 0,
        0, 0, 2, 2, 2, 0, 0
    };

    int* start_board = new int[ARR_SIZE] {
        0, 0, 1, 1, 1, 0, 0,
        0, 1, 1, 1, 1, 1, 0,
        1, 1, 1, 2, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 0,
        0, 0, 1, 1, 1, 0, 0
    };

    fringe.push(start_board);

    int one_count = 0;
    int min = 100;

    while (!fringe.empty()) {
        int* this_board = fringe.top();
        fringe.pop();

        //Check if this is a winning board
        bool win = true;
        int one_count = 0;
        for (int i = 0; i < ARR_SIZE; i++) {
            if (this_board[i] != win_board[i]) {
                win = false;
            }

            if (this_board[i] == 1) {
                one_count++;
            }
        };

        if (one_count < min) {
            min = one_count;
            std::cout << "------------------------" << std::endl;
            std::cout << min << std::endl;
			std::cout << fringe.size() << std::endl;
            printBoard(this_board);
            std::cout << "------------------------" << std::endl;            
        }

        //Check if we have won
        if (win) {
			std::cout << "WIN" << std::endl;
            printBoard(this_board);
            return 1;
        }

        for (int i = 0; i < ARR_SIZE; i++) {
            if (this_board[i] == 2) {
                int row = i / WIDTH;
                int col = i % WIDTH;
                if (row >= 2) {
                    applyBoardChanges(this_board, i - WIDTH * 2, i - WIDTH, i, fringe, check_position);
                }
                if (row <= 4) {
                    applyBoardChanges(this_board, i + WIDTH * 2, i + WIDTH, i, fringe, check_position);
                }
                if (col >= 2) {
                    applyBoardChanges(this_board, i - 2, i - 1, i, fringe, check_position);
                }
                if (col <= 4) {
                    applyBoardChanges(this_board, i + 2, i + 1, i, fringe, check_position);
                }
            }
         }
		delete[] this_board;
    }
}

void applyBoardChanges(int* old_board, int check1, int check2, int i, std::stack<int*> &fringe, std::unordered_map<std::string,bool> &check_position) {
	int* new_board = new int[ARR_SIZE];

	for (int i = 0; i < ARR_SIZE; i++) {
		new_board[i] = old_board[i];
	}

    if (old_board[check1] == 1 && old_board[check2] == 1) {
        new_board[i] = 1;
        new_board[check2] = 2;
        new_board[check1] = 2;
    }
    else {
		delete[] new_board;
        new_board = nullptr;
    }

    if (new_board) {
        std::string board_string = convert_array(new_board);
        std::unordered_map<std::string,bool>::const_iterator in_map = check_position.find(board_string);
        if (in_map == check_position.end()) {
            fringe.push(new_board);
            check_position[board_string] = true;
        }
        else {
			delete[] new_board;
        }
    }
}

std::string convert_array(int* board) {
    std::string new_array = "";

    for (int i = 0; i < ARR_SIZE; i++) {
		if (board[i] != 0) {
			new_array.append(std::to_string(board[i]));
		}
    }
    return new_array;
}

void printBoard(int* board) {
    for (int y = 0; y < WIDTH; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int pos = y * WIDTH + x;
            if (board[pos] == 0) {
				std::cout << "[#]";
            }
			else if (board[pos] == 1) {
				std::cout << "[+]";
			}
			else {
				std::cout << "[ ]";
			}
        }
        std::cout << "" << std::endl;
    }
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
}

int main() {

    std::cout << depthFirstSearch() << std::endl;

	system("PAUSE");

    return 1;
}