#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#define M 1000000007
#define ll long long int
#define pb push_back
#define pf push_front
#define all(x) x.begin(), x.end()
#define pob pop_back
#define pof pop_front
#define debug1(x) cout<<#x<<" "<<x<<endl;
#define debug2(x,y) cout<<#x<<" "<<x<<"   "<<#y<<" "<<y<<endl;
#define debug3(x,y,z) cout<<#x<<" "<<x<<"   "<<#y<<" "<<y<<"   "<<#z<<" "<<z<<endl;
#define debug4(x,y,z,p) cout<<#x<<" "<<x<<"   "<<#y<<" "<<y<<"   "<<#z<<" "<<z<<" "<<#p<<" "<<p<<endl;
#define vll      vector<ll> 
#define vvll     vector<vector<ll>>
#define fi first
#define se second
#define boost ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define inf 1e18
#define endl '\n'
typedef pair<int, int>		pii;
typedef pair<ll, ll>		pll;
#define pi (3.14159265358979323846264338327950288)
template<typename T>
void printv(const T& t) {std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));cout<<endl;}
ll modpower(ll a, ll b, ll mod) { ll res = 1; for (; b; b >>= 1) { if (b & 1)res = res * a; res %= mod; a = a * a; a %= mod; }return res; }
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
//unordered_map<ll,ll, custom_hash>m1;
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
ll mod_inv(ll a, ll b) {return expo(a, b - 2, b);}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, mod_inv(b, m), m) + m) % m;}
//-------------------------------Template--Above-----------------------------------------------
struct pos{
	ll x;ll y;
};
ll n,m;
char curr;
ll opp;
ll mine;
ll dx[8]={1,-1,0,0,1,1,-1,-1};
ll dy[8]={0,0,1,-1,1,-1,1,-1};
bool valid(ll x,ll y){
	if(x<0 || x>=n || y<0 || y>=m)return false;
	return true;
}
ll freeboard(ll board_number,vector<vll>grid){  // To find lowest board number if current board is already filled
	ll ix=(board_number/3)*3;
	ll iy=(board_number%3)*3;
	for(ll i=ix;i<ix+3;i++){
		for(ll j=iy;j<iy+3;i++){
			if(grid[i][j]==0)return board_number;
		}
	}
	for(ll k=0;k<9;k++){
		ll ix=(k/3)*3;
		ll iy=(k%3)*3;
		for(ll i=ix;i<ix+3;i++){
			for(ll j=iy;j<iy+3;i++){
				if(grid[i][j]==0)return k;
			}
		}
	}
	return -1;
}
pll findnext(ll px,ll py,vector<vll>grid){ // find next active board
	ll board_number=px/3;board_number*=3;
	board_number+=py/3;
	ll ix=(board_number/3)*3;
	ll iy=(board_number%3)*3;
	ll local_board=abs(ix-px)*3+abs(iy-py);
	local_board=freeboard(local_board,grid);
	if(local_board==-1)exit(0);
	ll startrow=(local_board/3)*3;
	ll startcol=(local_board%3)*3;
	return {startrow,startcol};
}
bool possible(vector<vector<ll> >grid){
	for(ll i=0;i<n;i++){
		for(ll j=0;j<m;j++){
			if(grid[i][j]==0)return true;
		}
	}
	return false;
}
ll evaluate(vector<vector<ll> >grid,ll depth){
	for(ll i=0;i<n;i++){
		for(ll j=0;j<m;j++){
			if(grid[i][j]!=0){
				ll num=grid[i][j];
				for(ll k=0;k<8;k++){
					if(valid(i+dx[k],j+dy[k]) and grid[i+dx[k]][j+dy[k]]==num 
					and valid(i+2*dx[k],j+2*dy[k]) and grid[i+2*dx[k]][j+2*dy[k]]==num
					and valid(i+3*dx[k],j+3*dy[k]) and grid[i+3*dx[k]][j+3*dy[k]]==num){
						if(num==mine)return 100-5*curr;
						return -100+5*curr;
					}
				}
			}
		}
	}
	return 0;
}
ll minimax(vector<vector<ll> >grid,ll depth,bool flag,ll px,ll py,ll alpha,ll beta){
	if(depth>3)return 0;
	ll curr=evaluate(grid,depth);
	if(curr!=0)return curr;
	pll p=findnext(px,py,grid);
	if(p.fi==-1 || p.se==-1)return 0;
	if(!possible(grid))return 0;
	ll startrow=p.fi,startcol=p.se;
	if(flag){
		ll maxi=-inf;
		for(ll i=startrow;i<min(startrow+3,n);i++){
			for(ll j=startcol;j<min(startcol+3,m);j++){
				if(grid[i][j]==0){
					grid[i][j]=mine;
					ll val=minimax(grid,depth+1,!flag,i,j,alpha,beta);
					maxi=max(maxi,val);
					alpha=max(alpha,maxi);
					grid[i][j]=0;
				}
				if(beta<=alpha)break;
			}
			if(beta<=alpha)break;
		}
		return maxi;
	}
	ll mini=inf;
	for(ll i=startrow;i<startrow+3;i++){
		for(ll j=startcol;j<startcol+3;j++){
			if(grid[i][j]==0){
				grid[i][j]=opp;
				ll val=minimax(grid,depth+1,!flag,i,j,alpha,beta);
				mini=min(mini,val);
				grid[i][j]=0;
				beta=min(beta,mini);
			}
			if(beta<=alpha)break;
		}
		if(beta<=alpha)break;
	}
	return mini;
}
pos findbest(vector<vector<ll> >grid,ll startrow,ll startcol){ 
	pos ans={-1,-1};
	ll maxi=-inf;
	for(ll i=startrow;i<min(startrow+3,n);i++){
		for(ll j=startcol;j<min(startcol+3,m);j++){
			if(grid[i][j]==0){
				grid[i][j]=mine;
				ll curr=minimax(grid,0,false,i,j,-inf,inf);
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
	ll k;cin>>k;
	cin>>n>>m;
	vector<vll>grid(n,vll(m));
	for(ll i=0;i<n;i++){
		for(ll j=0;j<m;j++){
			cin>>grid[i][j];
		}
	}
	ll px,py;
	cin>>opp>>px>>py;
	mine=(opp==2)?1:2;
	ll startrow,startcol;
	if(px<0 || py<0){
		startrow=3;
		startcol=3;
	}
	else{
		pll p=findnext(px,py,grid);
		startrow=p.fi,startcol=p.se;
	}
	pos ans=findbest(grid,startrow,startcol);
	cout<<ans.x<<" "<<ans.y<<endl;
    return;
}
int main()
{
    boost
    /*
    freopen("moocast.in", "r", stdin);
	freopen("moocast.out", "w", stdout);
	*/
    ll t;
    t=1;
   // cin>>t;
    for(ll i=1;i<=t;i++){
    	//cout << "Case #" << i << ": "; solve();
    	solve();
	}
    return 0;
}
