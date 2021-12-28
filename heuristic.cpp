#include<bits/stdc++.h>
#include<vector>

extern char opp, mine;
extern int n, m;

// FOR TESTING ONLY
// int opp, mine;
// long long n, m;

std::vector<int> search(std::vector<std::vector<char>> &grid, bool flag, int px, int py)
{
    std::vector<int> result(4);
    char mine_player = (flag ? mine : opp);
    char opp_player = (flag ? opp: mine);

    for(int row = px; row < px + 3; row++)
    {
        int free_inside = 0, free_outside = 0, mine_cnt = 0, opp_cnt = 0;

        for(int j = std::max(0, py - 3); j < std::max(0, py - 3) + 3; j++)
        {
            if(grid[row][j] == '0')
            {
                if(j < py || j >= py + 3) free_outside++;
                else free_inside++;
            }
            else if(grid[row][j] == mine_player) mine_cnt++;
            else opp_cnt++;
        }

        for(int col = std::max(0, py - 3); col < py + 3 && col + 3 < m; col++)
        {
            int j = col + 3;
            if(grid[row][j] == '0')
            {
                if(j < py || j >= py + 3) free_outside++;
                else free_inside++;
            }
            else if(grid[row][j] == mine_player) mine_cnt++;
            else opp_cnt++;

            // std::cout<<row<<", "<<col<<"\n";
            // std::cout<<free_inside<<" "<<free_outside<<" "<<mine_cnt<<" "<<opp_cnt<<"\n";

            if(free_inside && !opp_cnt)
            {
                int tot_free = free_inside + free_outside;
                result[tot_free - 1]++;
            }

            j = col;
            if(grid[row][j] == '0')
            {
                if(j < py || j >= py + 3) free_outside--;
                else free_inside--;
            }
            else if(grid[row][j] == mine_player) mine_cnt--;
            else opp_cnt--;
        }
    }


    // for(int i = 0; i < n; i++)
    // {
    //     std::cout<<i<<": "<<result[i]<<"\n";
    // }

    // std::cout<<"\n";


    for(int col = py; col < py + 3; col++)
    {
        int free_inside = 0, free_outside = 0, mine_cnt = 0, opp_cnt = 0;

        for(int j = std::max(0, px - 3); j < std::max(0, px - 3) + 3; j++)
        {
            if(grid[j][col] == '0')
            {
                if(j < px || j >= px + 3) free_outside++;
                else free_inside++;
            }
            else if(grid[j][col] == mine_player) mine_cnt++;
            else opp_cnt++;
        }

        for(int row = std::max(0, px - 3); row < px + 3 && row + 3 < n; row++)
        {
            int j = row + 3;
            if(grid[j][col] == '0')
            {
                if(j < px || j >= px + 3) free_outside++;
                else free_inside++;
            }
            else if(grid[j][col] == mine_player) mine_cnt++;
            else opp_cnt++;

            if(free_inside && !opp_cnt)
            {
                int tot_free = free_inside + free_outside;
                // std::cout<<"col: "<<col<<"\n";
                result[tot_free - 1]++;
            }

            j = row;
            if(grid[j][col] == '0')
            {
                if(j < px || j >= px + 3) free_outside--;
                else free_inside--;
            }
            else if(grid[j][col] == mine_player) mine_cnt--;
            else opp_cnt--;
        }
    }

    return result;
}

int heuristic(std::vector<std::vector<char>> &grid,int depth,bool flag,int px,int py)
{
    std::vector<int> cnt_mine = search(grid, 1, px, py);
    std::vector<int> cnt_opp = search(grid, 0, px, py);

    int mi_val = -5000;
    int ma_val = 5000;

    for(int i = 0; i < 3; i++)
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
//     {{1, 1, 2, 1, 0, 0},
//     {0, 0, 2, 0, 0, 0},
//     {0, 0, 0, 1, 0, 0}, 
//     {2, 0, 2, 2, 0, 0},
//     {0, 0, 0, 1, 0, 0}, 
//     {2, 0, 2, 2, 0, 0},};

//     /*
//         1 -> 1, 1,
//         2 -> 1, 1, 1,
//         3 -> 1, 1, 1
//         4 -> 1, 1,
//     */

//     n = 6, m = 6, mine = 1, opp = 2;
//     std::vector<int> res = search(grid, false, 1, 1);

//     for(int i = 0; i < 4; i++)
//     {
//         std::cout<<i<<": "<<res[i]<<"\n";
//     }

//     return 0;
// }

