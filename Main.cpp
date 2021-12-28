#include<bits/stdc++.h>
#include"code_warriors.h"
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#define boost std::ios_base::sync_with_stdio(false);std::cin.tie(NULL);std::cout.tie(NULL);
#define inf 1e9
#define endl '\n'
struct pos{
	int x;int y;
};

int n,m;
char curr;
char opp, mine;
int dx[8]={1,-1,0,0,1,1,-1,-1};
int dy[8]={0,0,1,-1,1,-1,1,-1};

bool valid(int x,int y){
	if(x<0 || x>=n || y<0 || y>=m)return false;
	return true;
}

int evaluate(std::vector<std::vector<char>> &grid,int depth){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(grid[i][j]!='0'){
				char num=grid[i][j];
				for(int k=0;k<8;k++){
					if(valid(i+dx[k],j+dy[k]) and grid[i+dx[k]][j+dy[k]]==num 
					and valid(i+2*dx[k],j+2*dy[k]) and grid[i+2*dx[k]][j+2*dy[k]]==num
					and valid(i+3*dx[k],j+3*dy[k]) and grid[i+3*dx[k]][j+3*dy[k]]==num){
						if(num==mine)return 10000-500*depth;
						return -10000+500*depth;
					}
				}
			}
		}
	}
	return 0;
}

int minimax(std::vector<std::vector<char> >&grid,int depth,bool flag,int px,int py,int alpha,int beta){
	if(depth>3)
	{
		std::pair<int, int> p=findnext(px,py,grid);
		if(p.first==-1 || p.second==-1)return 0;
		if(!is_move_possible(grid))return 0;	

		return heuristic(grid, depth, flag, p.first, p.second);
	}

	int curr=evaluate(grid,depth);
	if(curr!=0)return curr;
	std::pair<int, int> p=findnext(px,py,grid);
	if(p.first==-1 || p.second==-1)return 0;
	if(!is_move_possible(grid))return 0;


	int startrow=p.first,startcol=p.second;
	if(flag){
		int maxi=-inf;
		for(int i=startrow;i<std::min(startrow+3,n);i++){
			for(int j=startcol;j<std::min(startcol+3,m);j++){
				if(grid[i][j]=='0'){
					grid[i][j]=mine;
					int val=minimax(grid,depth+1,!flag,i,j,alpha,beta);
					maxi=std::max(maxi,val);
					alpha=std::max(alpha,maxi);
					grid[i][j]='0';
				}
				if(beta<=alpha)break;
			}
			if(beta<=alpha)break;
		}
		return maxi;
	}

	int mini=inf;
	for(int i=startrow;i<startrow+3;i++){
		for(int j=startcol;j<startcol+3;j++){
			if(grid[i][j]=='0'){
				grid[i][j]=opp;
				int val=minimax(grid,depth+1,!flag,i,j,alpha,beta);
				mini=std::min(mini,val);
				grid[i][j]='0';
				beta=std::min(beta,mini);
			}
			if(beta<=alpha)break;
		}
		if(beta<=alpha)break;
	}
	return mini;
}

pos findbest(std::vector<std::vector<char> >&grid,int startrow,int startcol){ 
	pos ans={-1,-1};
	int maxi=-inf;
	for(int i=startrow;i<std::min(startrow+3,n);i++){
		for(int j=startcol;j<std::min(startcol+3,m);j++){
			if(grid[i][j]=='0'){
				grid[i][j]=mine;
				int curr=minimax(grid,0,false,i,j,-inf,inf);
				grid[i][j]='0';
				if(curr>maxi){
					maxi=curr;
					ans.x=i;
					ans.y=j;
				}
			}
		}
	}
	return ans;
}
void solve(){
	int k;
	std::cin>>k;
	std::cin>>n>>m;
	std::vector<std::vector<char>>grid(n,std::vector<char>(m));

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			int x;
			std::cin>>x;
			grid[i][j] = x + '0';
		}
	}

	// for(int i =0 ;i < n; i++)
	// {
	// 	for(int j = 0; j < m; j++)
	// 	{
	// 		std::cout<<(grid[i][j])<<" ";
		
	// 	}
	// 	std::cout<<"\n";
	// }

	// return;

	int px,py;
	int x;
	std::cin>>x;
	opp = x + '0';

	std::cin>>px>>py;
	mine=(opp=='2')?'1':'2';
	int startrow,startcol;
	if(px<0 || py<0){
		startrow=3;
		startcol=3;
	}
	else{
		std::pair<int, int> p=findnext(px,py,grid);
		startrow=p.first,startcol=p.second;
	}
	pos ans=findbest(grid,startrow,startcol);
	std::cout<<ans.x<<" "<<ans.y<<endl;
    return;
}

int main()
{
    boost
	solve();
    return 0;
}
