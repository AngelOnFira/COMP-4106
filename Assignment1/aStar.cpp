#include "aStar.h"

AStar::AStar() {

}

AStar::AStar(int* start_board) {
	std::cout << "Running the depth-first search" << std::endl;
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

	Node* startNode = new Node(start_board, NULL);
	fringe.push(startNode);
	open.insert({ startNode->boardSerialized , startNode});

	runSearch();
}

void AStar::runSearch() {
	while (!fringe.empty()) {
		thisState = fringe.top();
		fringe.pop();

		int* this_board = thisState->board;
		closed.insert({ thisState->boardSerialized, thisState });

		/*#TODO
			-if it is, see if the path is better

		Find its children
		*/

		//Check if this is a winning board
		bool win = true;
		int one_count = 0;
		for (int i = 0; i < ARR_SIZE; i++) {
			if (this_board[i] == 1) {
				one_count++;
			}
			if (one_count > 1) {
				win = false;
				break;
			}
		};

		//Check if we have won
		if (win) {
			std::cout << "COMPLETED" << std::endl;
			std::cout << "This solution took " << iterations << " iterations to complete." << std::endl;
			system("PAUSE");
			return;
		}

		for (int i = 0; i < ARR_SIZE; i++) {
			if (this_board[i] == 2) {
				int row = i / WIDTH;
				int col = i % WIDTH;
				if (row >= 2) {
					applyBoardChanges(i - WIDTH * 2, i - WIDTH, i);
				}
				if (row <= 4) {
					applyBoardChanges(i + WIDTH * 2, i + WIDTH, i);
				}
				if (col >= 2) {
					applyBoardChanges(i - 2, i - 1, i);
				}
				if (col <= 4) {
					applyBoardChanges(i + 2, i + 1, i);
				}
			}
		}
		iterations++;
	}
}

void AStar::applyBoardChanges(int check1, int check2, int curr_pos) {
	int* new_board = new int[ARR_SIZE];

	for (int i = 0; i < ARR_SIZE; i++) {
		new_board[i] = this_board[i];
	}

	if (this_board[check1] == 1 && this_board[check2] == 1) {
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
		std::unordered_map<std::string, Node*>::const_iterator in_open = open.find(board_string);
		std::unordered_map<std::string, Node*>::const_iterator in_closed = closed.find(board_string);
		if (in_open == open.end() && in_closed == closed.end()) {
			Node* newState = new Node(new_board, thisState);
			fringe.push(newState);
			open.insert({ newState->boardSerialized, newState });

			//Add as child of parent
			thisState->addChild(newState);
		}
		else if (in_open == open.end() && in_closed != closed.end()) {
			Node* alreadyState = closed[board_string];
			Node* newState = new Node(new_board, thisState);

			if (newState->score < alreadyState->score) {
				alreadyState->parent->removeChild(alreadyState);
				thisState->addChild(alreadyState);
				alreadyState->calculateScore();
			}
			delete[] newState;
		}
		else {
			delete[] new_board;
		}
	}
}

std::string AStar::convert_array(int* board) {
	std::string new_array = "";

	for (int i = 0; i < ARR_SIZE; i++) {
		if (board[i] != 0) {
			new_array.append(std::to_string(board[i]));
		}
	}
	return new_array;
}

void AStar::printBoard(int* board) {
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

void AStar::sortFringe() {
	std::vector<Node*> tempFringe;

	while (!fringe.empty()) {
		tempFringe.push_back(fringe.top());
		fringe.pop();
	}

	while (!tempFringe.empty()) {
		fringe.push(tempFringe.back());
		tempFringe.pop_back();
	}
}