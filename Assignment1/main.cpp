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

	/*int* start_board = new int[ARR_SIZE] {
		0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 2, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 1, 0, 0, 0,
	};*/

	//DepthFirst depth_first_search = DepthFirst(start_board);
	//BreadthFirst breadth_first_search = BreadthFirst(start_board);
	AStar aStarSearch = AStar(start_board);

	system("PAUSE");

    return 1;
}