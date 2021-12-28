#include<bits/stdc++.h>
#include<vector>

extern int opp, mine;
extern long long n, m;

// FOR TESTING ONLY
// int opp, mine;
// long long n, m;

std::vector<std::pair<int, int>> search_3(std::vector<std::vector<long long>> &grid, bool flag, int px, int py)
{
    std::vector<std::pair<int, int>> result;
    int cur_player = (flag ? mine : opp);

    for(int row = px; row < px + 3; row++)
    {
        for(int col = py; col < py + 3; col++)
        {
            if(grid[row][col] == 0)
            {
                bool first_check = false;
                // check whether possible or not
                // check vertically
                for(int first_row = std::max(0, row - 3); first_row <= row && first_row + 3 < n; first_row++)
                {
                    bool possible = true;
                    for(int it = first_row; it < first_row + 3; it++)
                    {
                        if(it == row) continue;
                        if(grid[it][col] != cur_player) {possible = false; break;}
                    }

                    if(possible)
                    {
                        result.push_back({row, col});
                        first_check = true;
                        break;
                    }
                }

                if(first_check) break;

                // check horizontally
                for(int first_col = std::max(0, col - 3); first_col <= col && first_col + 3 < m; first_col++)
                {
                    bool possible = true;
                    for(int it = first_col; it < first_col + 3; it++)
                    {
                        if(it == col) continue;
                        if(grid[row][it] != cur_player) {possible = false; break;}
                    }

                    if(possible)
                    {
                        result.push_back({row, col});
                        break;
                    }
                }

            }
        }
    }

    return result;
}

long long heuristic(std::vector<std::vector<long long> >grid,long long depth,bool flag,long long px,long long py)
{
    search_3(grid, false, 0, 0);
    return 0;
}

// FOR TESTING ONLY

/*
int main()
{
    std::vector<std::vector<long long>> grid = 
    {{1, 1, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1}, 
    {2, 0, 2, 2}};

    n = 4, m = 4, mine = 1, opp = 2;
    std::vector<std::pair<int, int>> res = search(grid, 0, 1, 1);

    std::cout<<res.size()<<"\n";

    for(auto e: res)
    {
        std::cout<<e.first<<' '<<e.second<<"\n";
    } 

    return 0;
}
*/
