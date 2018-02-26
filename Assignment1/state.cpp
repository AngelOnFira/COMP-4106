#include "state.h"

Node::Node(int* board, Node* parent) {
	this->parent = parent;
	this->board = board;

	if (parent) {
		this->depth = parent->depth + 1;
	}

	proximityHeuristic();
	serializeBoard();
}

void Node::proximityHeuristic() {
	int* scoreBoard = new int[ARR_SIZE] {
		0    , 0    , 0.83f, 1, 0.83f, 0    , 0    ,
		0    , 1.17f, 1.76f, 2, 1.76f, 1.17f, 0    ,
		0.83f, 1.76f, 2.59f, 3, 2.59f, 1.76f, 0.83f,
		1    , 2    , 3    , 4, 3    , 2    , 1    ,
		0.83f, 1.76f, 2.59f, 3, 2.59f, 1.76f, 0.83f,
		0    , 1.17f, 1.76f, 2, 1.76f, 1.17f, 0    ,
		0    , 0    , 0.83f, 1, 0.83f, 0    , 0
	};

	float addScore = 0;
	int countPegs = 0;

	for (int i = 0; i < 7; i++) {
		if (board[i] == 1) {
			countPegs++;
			addScore += scoreBoard[i];
		}
	}

	proximityScore = addScore / (countPegs * 4.00f);
}

void Node::serializeBoard() {
	std::string new_array = "";

	for (int i = 0; i < ARR_SIZE; i++) {
		if (board[i] != 0) {
			new_array.append(std::to_string(board[i]));
		}
	}
	boardSerialized = new_array;
}

void Node::addChild(Node* child) {
	children.push_back(child);
}