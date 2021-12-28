#include<bits/stdc++.h>
#include"code_warriors.h"
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#define boost std::ios_base::sync_with_stdio(false);std::cin.tie(NULL);std::cout.tie(NULL);
#define inf 1e18
#define endl '\n'

struct pos{
	long long x;long long y;
};

long long n,m;
char curr;
int opp, mine;
long long dx[8]={1,-1,0,0,1,1,-1,-1};
long long dy[8]={0,0,1,-1,1,-1,1,-1};

bool valid(long long x,long long y){
	if(x<0 || x>=n || y<0 || y>=m)return false;
	return true;
}

long long evaluate(std::vector<std::vector<long long>> &grid,long long depth){
	for(long long i=0;i<n;i++){
		for(long long j=0;j<m;j++){
			if(grid[i][j]!=0){
				long long num=grid[i][j];
				for(long long k=0;k<8;k++){
					if(valid(i+dx[k],j+dy[k]) and grid[i+dx[k]][j+dy[k]]==num 
					and valid(i+2*dx[k],j+2*dy[k]) and grid[i+2*dx[k]][j+2*dy[k]]==num
					and valid(i+3*dx[k],j+3*dy[k]) and grid[i+3*dx[k]][j+3*dy[k]]==num){
						if(num==mine)return 10000-5*curr;
						return -10000+5*curr;
					}
				}
			}
		}
	}
	return 0;
}

long long minimax(std::vector<std::vector<long long> >grid,long long depth,bool flag,long long px,long long py,long long alpha,long long beta){
	if(depth>2)
	{
		std::pair<long long, long long> p=findnext(px,py,grid);
		if(p.first==-1 || p.second==-1)return 0;
		if(!is_move_possible(grid))return 0;	

		return heuristic(grid, depth, flag, p.first, p.second);
	}

	long long curr=evaluate(grid,depth);
	if(curr!=0)return curr;
	std::pair<long long, long long> p=findnext(px,py,grid);
	if(p.first==-1 || p.second==-1)return 0;
	if(!is_move_possible(grid))return 0;


	long long startrow=p.first,startcol=p.second;
	if(flag){
		long long maxi=-inf;
		for(long long i=startrow;i<std::min(startrow+3,n);i++){
			for(long long j=startcol;j<std::min(startcol+3,m);j++){
				if(grid[i][j]==0){
					grid[i][j]=mine;
					long long val=minimax(grid,depth+1,!flag,i,j,alpha,beta);
					maxi=std::max(maxi,val);
					alpha=std::max(alpha,maxi);
					grid[i][j]=0;
				}
				if(beta<=alpha)break;
			}
			if(beta<=alpha)break;
		}
		return maxi;
	}

	long long mini=inf;
	for(long long i=startrow;i<startrow+3;i++){
		for(long long j=startcol;j<startcol+3;j++){
			if(grid[i][j]==0){
				grid[i][j]=opp;
				long long val=minimax(grid,depth+1,!flag,i,j,alpha,beta);
				mini=std::min(mini,val);
				grid[i][j]=0;
				beta=std::min(beta,mini);
			}
			if(beta<=alpha)break;
		}
		if(beta<=alpha)break;
	}
	return mini;
}

pos findbest(std::vector<std::vector<long long> >grid,long long startrow,long long startcol){ 
	pos ans={-1,-1};
	long long maxi=-inf;
	for(long long i=startrow;i<std::min(startrow+3,n);i++){
		for(long long j=startcol;j<std::min(startcol+3,m);j++){
			if(grid[i][j]==0){
				grid[i][j]=mine;
				long long curr=minimax(grid,0,false,i,j,-inf,inf);
				grid[i][j]=0;
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
	long long k;
	std::cin>>k;
	std::cin>>n>>m;
	std::vector<std::vector<long long>>grid(n,std::vector<long long>(m));

	for(long long i=0;i<n;i++){
		for(long long j=0;j<m;j++){
			std::cin>>grid[i][j];
		}
	}
	long long px,py;
	std::cin>>opp>>px>>py;
	mine=(opp==2)?1:2;
	long long startrow,startcol;
	if(px<0 || py<0){
		startrow=3;
		startcol=3;
	}
	else{
		std::pair<long long, long long> p=findnext(px,py,grid);
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
