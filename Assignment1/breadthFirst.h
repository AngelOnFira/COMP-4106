#pragma once

#include "includes.h"

class BreadthFirst {
public:
	BreadthFirst();
	BreadthFirst(int* input_board);
	void runSearch();
	void applyBoardChanges(int* old_board, int check1, int check2, int curr_pos, std::vector<int>* old_path);
	std::string convert_array(int* board);
	void printBoard(int* board);

	int one_count = 0;
	int min = 100;
	int iterations = 0;
	bool compare = true;
	int* win_board;
	int* start_board;
	int* path_board;

	std::queue<int*> fringe;
	std::queue<std::vector<int>*> breadcrumbs;
	std::unordered_map<std::string, bool> check_position;
};
