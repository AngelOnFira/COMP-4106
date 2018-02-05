#include "breadthFirst.h"

BreadthFirst::BreadthFirst() {

}

BreadthFirst::BreadthFirst(int* start_board) {
	std::cout << "Running the breadth-first search" << std::endl;
	win_board = new int[ARR_SIZE] {
		0, 0, 2, 2, 2, 0, 0,
		0, 2, 2, 2, 2, 2, 0,
		2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 1, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2,
		0, 2, 2, 2, 2, 2, 0,
		0, 0, 2, 2, 2, 0, 0
	};

	this->start_board = start_board;

	fringe.push(start_board);
	std::vector<int>* start_path = new std::vector<int>();
	breadcrumbs.push(start_path);

	runSearch();
}

void BreadthFirst::runSearch() {
	while (!fringe.empty()) {
		int* this_board = fringe.front();
		fringe.pop();

		std::vector<int>* this_path = breadcrumbs.front();
		breadcrumbs.pop();

		//Check if this is a winning board
		bool win = true;
		int one_count = 0;
		for (int i = 0; i < ARR_SIZE; i++) {
			if (this_board[i] == 1) {
				one_count++;
			}
			if (one_count > 1) {
				win = false;
				//break;
			}
		};

		if (one_count < min) {
			min = one_count;
			std::cout << "Solved down to " << min << " pegs" << std::endl;
		}

		//Check if we have won
		if (win) {
			std::cout << "WIN" << std::endl;

			int* path_board = new int[ARR_SIZE] {
				0, 0, 1, 1, 1, 0, 0,
				0, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 2, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 1, 1, 1, 0,
				0, 0, 1, 1, 1, 0, 0
			};

			for (int i = 0; i < this_path->size(); i += 3) {
				printBoard(path_board);
				path_board[this_path->at(i)] = 2;
				path_board[this_path->at(i + 1)] = 2;
				path_board[this_path->at(i + 2)] = 1;
			}
			printBoard(path_board);
			std::cout << "This solution took " << iterations << " iterations to complete." << std::endl;
			system("PAUSE");
		}

		for (int i = 0; i < ARR_SIZE; i++) {
			if (this_board[i] == 2) {
				int row = i / WIDTH;
				int col = i % WIDTH;
				if (row >= 2) {
					applyBoardChanges(this_board, i - WIDTH * 2, i - WIDTH, i, this_path);
				}
				if (row <= 4) {
					applyBoardChanges(this_board, i + WIDTH * 2, i + WIDTH, i, this_path);
				}
				if (col >= 2) {
					applyBoardChanges(this_board, i - 2, i - 1, i, this_path);
				}
				if (col <= 4) {
					applyBoardChanges(this_board, i + 2, i + 1, i, this_path);
				}
			}
		}
		iterations++;
		delete[] this_board;
	}
}

void BreadthFirst::applyBoardChanges(int* old_board, int check1, int check2, int curr_pos, std::vector<int>* old_path) {
	int* new_board = new int[ARR_SIZE];

	for (int i = 0; i < ARR_SIZE; i++) {
		new_board[i] = old_board[i];
	}

	if (old_board[check1] == 1 && old_board[check2] == 1) {
		new_board[curr_pos] = 1;
		new_board[check2] = 2;
		new_board[check1] = 2;
	}
	else {
		delete[] new_board;
		new_board = nullptr;
	}

	if (new_board) {
		std::string board_string = convert_array(new_board);
		std::unordered_map<std::string, bool>::const_iterator in_map = check_position.find(board_string);
		if (in_map == check_position.end()) {
			fringe.push(new_board);
			check_position[board_string] = true;

			std::vector<int>* new_path = new std::vector<int>();
			for (int i = 0; i < old_path->size(); i++) {
				new_path->push_back(old_path->at(i));
			}
			new_path->push_back(check1);
			new_path->push_back(check2);
			new_path->push_back(curr_pos);
			breadcrumbs.push(new_path);
		}
		else {
			delete[] new_board;
		}
	}
}

std::string BreadthFirst::convert_array(int* board) {
	std::string new_array = "";

	for (int i = 0; i < ARR_SIZE; i++) {
		if (board[i] != 0) {
			new_array.append(std::to_string(board[i]));
		}
	}
	return new_array;
}

void BreadthFirst::printBoard(int* board) {
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