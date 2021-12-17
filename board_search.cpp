#include<vector>
#include<utility>
#include<cstdlib>

long long freeboard(long long board_number,std::vector<std::vector<long long>>grid){  // To find lowest board number if current board is already filong longed
	long long ix=(board_number/3)*3;
	long long iy=(board_number%3)*3;
	for(long long i=ix;i<ix+3;i++){
		for(long long j=iy;j<iy+3;i++){
			if(grid[i][j]==0)return board_number;
		}
	}
	for(long long k=0;k<9;k++){
		long long ix=(k/3)*3;
		long long iy=(k%3)*3;
		for(long long i=ix;i<ix+3;i++){
			for(long long j=iy;j<iy+3;i++){
				if(grid[i][j]==0)return k;
			}
		}
	}
	return -1;
}

// find next active board
std::pair<long long, long long> findnext(long long px,long long py,std::vector<std::vector<long long>>grid){ 
	long long board_number=px/3;board_number*=3;
	board_number+=py/3;
	long long ix=(board_number/3)*3;
	long long iy=(board_number%3)*3;
	long long local_board=std::abs(ix-px)*3+std::abs(iy-py);
	local_board=freeboard(local_board,grid);
	if(local_board==-1)exit(0);
	long long startrow=(local_board/3)*3;
	long long startcol=(local_board%3)*3;
	return {startrow,startcol};
}