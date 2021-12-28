#ifndef CODE_WARRIORS
#define CODE_WARRIORS
#include<vector>
#include<utility>
#include<cstdlib>

int freeboard(int board_number,std::vector<std::vector<char>> &grid);
std::pair<int, int> findnext(int px,int py,std::vector<std::vector<char>> &grid);
bool is_move_possible(std::vector<std::vector<char>> &);
int heuristic(std::vector<std::vector<char> >&grid,int depth,bool flag,int px,int py);

#endif