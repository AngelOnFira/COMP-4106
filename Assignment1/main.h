#include "includes.h"
#include "depthFirst.h"

int* createNewBoard(int* old_board);
int depthFirstSearch();
void applyBoardChanges(
	int* board,
	int check1,
	int check2,
	int curr_pos,
	std::stack<int*> &fringe,
	std::unordered_map<std::string,bool> &check_position,
	std::vector<int>* old_path,
	std::stack<std::vector<int>*> &breadcrumbs
);

void printBoard(int* board);
std::string convert_array(int* board);