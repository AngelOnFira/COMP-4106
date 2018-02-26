#pragma once

#include "includes.h"

class Node {
public:
	Node();
	Node(int* board, Node* parent);

	void proximityHeuristic();
	void serializeBoard();
	void addChild(Node* child);

	Node* parent;
	std::vector<Node*> children;

	std::string boardSerialized;
	int* board;

	float score;
	float proximityScore;
	float viableMoveScore;
	int depth = 0;
};
