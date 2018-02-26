#pragma once

#include "includes.h"
#include "state.h"

class AStar {
public:
	AStar();
	AStar(int* start_board);
	void runSearch();
	void applyBoardChanges(int check1, int check2, int curr_pos);
	std::string convert_array(int* board);
	void printBoard(int* board);
	void sortFringe();

	int one_count = 0;
	int min = 100;
	int iterations = 0;
	bool compare = true;
	int* win_board;
	int* start_board;
	int* this_board;
	Node* thisState;

	std::priority_queue<Node*, std::vector<Node*>, compareScore> fringe;
	std::unordered_map<std::string, Node*> open;
	std::unordered_map<std::string, Node*> closed;
};

struct compareScore {
	bool operator()(const Node& node_1, const Node& node_2) const
	{
		return node_1.score > node_2.score;
	}

	bool operator()(const Node *node_1, const Node *node_2) const
	{
		return node_1->score > node_2->score;
	}
};
