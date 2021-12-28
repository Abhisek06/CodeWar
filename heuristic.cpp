#include<bits/stdc++.h>
#include<vector>

extern int opp, mine;
extern long long n, m;

// FOR TESTING ONLY
// int opp, mine;
// long long n, m;

std::vector<std::vector<std::pair<int, int>>> search(std::vector<std::vector<long long>> &grid, bool flag, int px, int py)
{
    std::vector<std::vector<std::pair<int, int>>> result(4);
    int cur_player = (flag ? mine : opp);
    int opp_player = (flag ? opp: mine);

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
                    int spaces = 0;
                    for(int it = first_row; it <= first_row + 3; it++)
                    {
                        if(grid[it][col] == opp_player) {possible = false; break;}
                        spaces += !grid[it][col];
                    }

                    if(possible)
                    {
                        result[spaces - 1].push_back({row, col});
                        first_check = true;
                        break;
                    }
                }

                /* Should I remove it or no?? */
                if(first_check) break;

                // check horizontally
                for(int first_col = std::max(0, col - 3); first_col <= col && first_col + 3 < m; first_col++)
                {
                    bool possible = true;
                    int spaces = 0;
                    for(int it = first_col; it <= first_col + 3; it++)
                    {
                        if(grid[row][it] == opp_player) {possible = false; break;}
                        spaces += !grid[row][it];
                    }

                    if(possible)
                    {
                        result[spaces - 1].push_back({row, col});
                        break;
                    }
                }

            }
        }
    }

    return result;
}

long long heuristic(std::vector<std::vector<long long> > grid,long long depth,bool flag,long long px,long long py)
{
    /* No requirement of positions!!!!!!!!!!!!*/
    std::vector<std::vector<std::pair<int, int>>> val = search(grid, true, px, py);
    std::vector<int> cnt_mine(4);
    for(int i = 0; i < 4; i++) cnt_mine[i] += val[i].size();

    val = search(grid, false, px, py);
    std::vector<int> cnt_opp(4);
    for(int i = 0; i < 4; i++) cnt_opp[i] += val[i].size();

    long long mi_val = -5000 + 5 * depth;
    long long ma_val = 5000 - 5 * depth;

    for(int i = 0; i < 4; i++)
    {
        if(cnt_mine[i] || cnt_opp[i])
        {
            if(flag)
            {
                // maximizing node
                if(cnt_mine[i] > cnt_opp[i]) return ma_val;
                else return mi_val;
            }
            else
            {
                // minimizing node
                if(cnt_mine[i] > cnt_opp[i]) return mi_val;
                else return ma_val;
            }
        }
    }

    return 0;
}

// FOR TESTING ONLY


// int main()
// {
//     std::vector<std::vector<long long>> grid = 
//     {{1, 1, 2, 1},
//     {0, 0, 2, 0},
//     {0, 0, 0, 1}, 
//     {2, 0, 2, 2}};

//     n = 4, m = 4, mine = 1, opp = 2;
//     std::vector<std::vector<std::pair<int, int>>> res = search(grid, 1, 1, 1);

//     std::cout<<res.size()<<"\n";

//     for(int i = 0; i < 4; i++)
//     {
//         std::cout<<i<<":\n";
//         for(auto e: res[i])
//         std::cout<<e.first<<' '<<e.second<<"\n";
    
//         std::cout<<"\n";
//     } 

//     return 0;
// }

