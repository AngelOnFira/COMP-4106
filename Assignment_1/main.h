#include <iostream>
#include <thread>
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>

int* createNewBoard(int* old_board);
int depthFirstSearch();
void applyBoardChanges(int* board, int check1, int check2, int i, std::stack<int*> &fringe, std::unordered_map<std::string,bool> &check_position);
void printBoard(int* board);
std::string convert_array(int* board);