#include <bits/stdc++.h>
#include <ctime>
#pragma gcc optimise('O3')
#include <cstdlib>
#define ii pair<int, int>
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define E13 10000000000000
#define DUMP(a) \
    do { std::cout << "[" << #a " = " << (a) << "]" <<  std::endl; } while(false)
#define d0(x) cout<<(x)<<" "
#define d1(x) cout<<(x)<<endl
#define edge pair<int, pair<int, int> > 
#define REP0(i, n) for (int i=0; i<n; ++i)
#define REP1(i, n) for (int i=1; i<=n; ++i)
#define d2(x,y) cout<<(x)<<" "<<(y)<<endl
#define d3(x,y,z) cout<<(x)<<" "<<(y)<<" "<<(z)<<endl
#define d4(a,b,c,d) cout<<(a)<<" "<<(b)<<" "<<(c)<<" "<<(d)<<endl
#define d5(a,b,c,d,e) cout<<(a)<<" "<<(b)<<" "<<(c)<<" "<<(d)<<" "<<(e)<<endl
#define d6(a,b,c,d,e,f) cout<<(a)<<" "<<(b)<<" "<<(c)<<" "<<(d)<<" "<<(e)<<" "<<(f)<<endl
using namespace std;

template<class T> ostream& operator<<(ostream &os, vector<T> V) {
    os << "[ ";
    for(auto v : V) os << v << " ";
    return os << "]";
}
template<class T> ostream& operator<<(ostream &os, set<T> S){
    os << "{ ";
    for(auto s:S) os<<s<<" ";
    return os<<"}";
}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {
    return os << "(" << P.first << "," << P.second << ")";
}
template<class L, class R> ostream& operator<<(ostream &os, map<L,R> M) {
    os << "{ ";
    for(auto m:M) os<<"("<<m.F<<":"<<m.S<<") ";
    return os<<"}";
}
int n, m;
int power(int base, int exp){
	if (exp==0)
		return 1;
	int res = power(base, exp/2);
	res = (res*res)%MOD;
	if (exp % 2)
		return (res*base)%MOD;
	return res;
}
int inverse(int n){
	return power(n, MOD-2);
}
void solve(){
	int n, m; scanf("%d %d", &n, &m);
	int mx = 1 << n;
	vector< vector<int> >  dp(n, vector<int>(mx));
	vector<int> adj[n];

	REP0(i, m){
		int a, b; scanf("%d %d", &a, &b);
		a--; b--;
		adj[a].pb(b); 
	}
	dp[n-1][mx-1] = 1;
	for (int i=mx-1; i>=0; --i){
		for (int j=0; j<n; ++j){
			if (i == mx-1 && j == n-1) continue;
			int comp = 1 << j;
			dp[j][i] = 0;
			if (!(comp & i)) continue;
			for (int to: adj[j]){
				comp = 1 << to;
				if (comp & i) continue;
				dp[j][i] = (dp[j][i] + dp[to][i|comp])%MOD;
			}

		}
	}
	cout << dp[0][1] << endl;
}

signed main(){
	// #ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
	// #endif
	solve();
	
	return 0;
}