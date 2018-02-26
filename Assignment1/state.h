#pragma once

#include "includes.h"

class Node {
public:
	Node();
	Node(int* board, Node* parent);

	void Node::proximityHeuristic();
	void Node::serializeBoard();

	Node* parent;
	std::vector<Node*> children;

	std::string boardSerialized;
	int* board;

	float score;
	float proximityScore;
	float viableMoveScore;
};
