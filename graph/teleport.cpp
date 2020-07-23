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
void dfs(int cur, vector<bool> &visited, vector<ii> adj[]){
	visited[cur] = 1;
	for (ii to: adj[cur]){
		if (!visited[to.first])
			dfs(to.first, visited, adj);
	}
}
void dfs2(int cur, vector<ii> adj[], vector<ii> &edges, vector<bool> &used, int &i, vector<bool> &bridge){
	bool got = false; ii sit;
	bool alt = false;
	for (ii to: adj[cur]){
		if (!used[to.second] && !bridge[to.second]){
			alt = true;
			used[to.second] = 1;
			edges[i] = mp(cur, to.first);
			i++;
			dfs2(to.first, adj, edges, used, i, bridge);
			break;
		}
		if (!used[to.second] && bridge[to.second]){
			got = true;
			sit = to;
		}
	}
	if (got && !alt){
		used[sit.second] = 1;
		edges[i] = mp(cur, sit.first);
		i++;
		dfs2(sit.first, adj, edges, used, i, bridge);
	}
}

void dfs3(int cur, vector<ii> adj[], vector<bool> &bridge, vector<int>& low, vector<int> &tin, int &j, vector<bool> &vv){
	vv[cur] = 1;
	tin[cur] = j;
	low[cur] = j;
	j++;
	for (ii to: adj[cur]){
		if (!vv[to.first]){
			dfs3(to.first, adj, bridge, low, tin, j, vv);
			low[cur] = min(low[cur], low[to.first]);
			if (low[to.first]==tin[cur]){
				bridge[to.second] = 1;
			}
		}
		else {
			low[cur] = min(low[cur], tin[to.first]);
		}
		
		
	}
}
void solve(){
	int n, m; cin >> n >> m;
	vector<ii> adj[n+1];
	bool pos = 1;
	for (int i=1; i<=m; ++i){
		int a, b;
		cin >> a >> b;
		adj[a].pb(mp(b, i));
		adj[b].pb(mp(a, i));
	}
	vector<bool> visited(n+1,false);
	for (int i=1; i<=n; ++i){
		if (!visited[i]){
			if (i != 1){
				if (adj[i].size() != 0){
					pos = 0; break;
				}
			}
			else {
				dfs(i, visited, adj);
			}
		}
	}
	if (!visited[n]){
		pos = 0;
	}
	if (!pos){
		d1("IMPOSSIBLE");
		return;
	}
	for (int i=2; i<n; ++i){
		if (visited[i]){
			if (adj[i].size()%2){
				pos = 0; break;
			}
		}
	}
	if (adj[1].size()%2==0 || adj[n].size()%2==0){
		pos = 0;
	}
	if (!pos){
		d1("IMPOSSIBLE");
		return;
	}
	vector<bool> used(m+1, false);
	vector<bool> bridge(m+1, false);
	vector<int> tin(n+1);
	vector<int> low(n+1);
	vector<ii> edges(m);
	vector<bool> vv(n+1,false);
	int j = 0;
	dfs3(1, adj, bridge, low, tin, j, vv);
	int i = 0;
	dfs2(1, adj, edges, used, i, bridge);

	d1(i-m);
	for (int i=0; i<m; i++){
		d0(edges[i].first);
	}
	d0(edges[m-1].second);
	cout << endl;
}

signed main(){
	// #ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
	// #endif
	solve();
	
	return 0;
}