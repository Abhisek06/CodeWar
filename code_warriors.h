#ifndef CODE_WARRIORS
#define CODE_WARRIORS

#include<vector>
#include<utility>
#include<cstdlib>

long long freeboard(long long board_number,std::vector<std::vector<long long>> &grid);
std::pair<long long, long long> findnext(long long px,long long py,std::vector<std::vector<long long>> &grid);
bool is_move_possible(std::vector<std::vector<long long>> &);
long long heuristic(std::vector<std::vector<long long> >grid,long long depth,bool flag,long long px,long long py);

#endif