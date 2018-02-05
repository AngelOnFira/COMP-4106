#include "main.h"

int main() {

	int* start_board = new int[ARR_SIZE] {
		0, 0, 1, 1, 1, 0, 0,
		0, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 2, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 0,
		0, 0, 1, 1, 1, 0, 0
	};

	int* start_board_easy = new int[ARR_SIZE] {
		0, 0, 2, 2, 2, 0, 0,
		0, 2, 2, 2, 2, 1, 0,
		1, 1, 2, 2, 1, 2, 2,
		1, 1, 1, 2, 1, 2, 2,
		1, 2, 2, 1, 1, 2, 2,
		0, 2, 2, 2, 1, 1, 0,
		0, 0, 2, 2, 1, 0, 0
	};

	int* start_board_bonus = new int[ARR_SIZE] {
		0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 2, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 1, 0, 0, 0,
	};

	//Run the partly-finished version of the game
	//DepthFirst depth_first_search = DepthFirst(start_board_easy);
	BreadthFirst breadth_first_search = BreadthFirst(start_board_easy);

	//Run the blank-slate version of the game
	DepthFirst depth_first_search = DepthFirst(start_board_easy);
	//BreadthFirst breadth_first_search = BreadthFirst(start_board_easy);

    return 1;
}