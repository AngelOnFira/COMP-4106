#pragma once

#include "includes.h"

class DepthFirst {
public:
	DepthFirst();
	void runSearch();

	int one_count = 0;
	int min = 100;
	int iterations = 0;
	bool compare = true;
	int* win_board;
	int* start_board;

	std::stack<int*> fringe;
	std::stack<std::vector<int>*> breadcrumbs;
	std::unordered_map<std::string, bool> check_position;
};