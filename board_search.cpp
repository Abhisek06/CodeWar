#include<vector>
#include<utility>
#include<cstdlib>
// To find lowest board number if current board is already fiinted
int freeboard(int board_number,std::vector<std::vector<char>> &grid){  
	int ix=(board_number/3)*3;
	int iy=(board_number%3)*3;

	for(int i=ix;i<ix+3;i++){
		for(int j=iy;j<iy+3;i++){
			if(grid[i][j]=='0')return board_number;
		}
	}
	for(int k=0;k<9;k++){
		int ix=(k/3)*3;
		int iy=(k%3)*3;
		for(int i=ix;i<ix+3;i++){
			for(int j=iy;j<iy+3;i++){
				if(grid[i][j]=='0')return k;
			}
		}
	}
	return -1;
}

// find next active board
std::pair<int, int> findnext(int px,int py,std::vector<std::vector<char>> &grid){ 
	int board_number=px/3;board_number*=3;
	board_number+=py/3;
	int ix=(board_number/3)*3;
	int iy=(board_number%3)*3;
	int local_board=std::abs(ix-px)*3+std::abs(iy-py);
	local_board=freeboard(local_board,grid);
	if(local_board==-1)exit(0);
	int startrow=(local_board/3)*3;
	int startcol=(local_board%3)*3;
	return {startrow,startcol};
}

bool is_move_possible(std::vector<std::vector<char>> &grid){
    int n = (int)grid.size(), m = (int)grid[0].size();
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(grid[i][j]=='0')
			{
				return true;
			}
		}
	}
	return false;
}