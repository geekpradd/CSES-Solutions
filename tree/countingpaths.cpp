#include <bits/stdc++.h>
#include <ctime>
#include <cstdlib>
#define int long long
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

void dfs(int cur, vector<int> adj[], vector<int>& euler, vector<int>&depth, vector<ii> &positions, int h, int &i, int p, vector< vector<int> > &lift){
	positions[cur].first = i;
	euler[i] = cur; i++;
	depth[cur] = h;
	lift[cur][0] = p;

	for (int to: adj[cur]){
		if (to == p) continue;
		dfs(to, adj, euler, depth, positions, h+1, i, cur, lift);
	}
	positions[cur].second = i;
	euler[i] = cur; i++;	
}

int is_ancestor(int a, int b, vector<ii> &positions){
	if (positions[a].first <= positions[b].first && positions[b].second <= positions[a].second){
		return true;
	}
	return false;
}

int lca(int a, int b, vector<ii> &positions, vector < vector<int> > &lift){
	if (is_ancestor(a, b, positions))
		return a;
	if (is_ancestor(b, a, positions))
		return b;
	int s = lift[1].size();
	for (int i=s-1; i>=0; --i){
		if (!is_ancestor(lift[a][i], b, positions)){
			a = lift[a][i];
		}
	}

	return lift[a][0];
}

void update(vector<int> &segtree, int i, int l, int r, int ql, int qr, int value, int pending){

	if (qr < l || ql > r){
		segtree[i] += pending;
		return;
	}
	if (l >= ql && r <= qr){
		segtree[i] += pending;
		segtree[i] += value;
		return;
	}
	int mid = (l+r)/2;
	pending += segtree[i];
	segtree[i] = 0;
	update(segtree, 2*i+1, l, mid, ql, qr, value, pending);
	update(segtree, 2*i+2, mid+1, r, ql, qr, value, pending);
}
int query(vector<int> &segtree, int i, int l, int r, int qi, int pending){

	if (qi < l || qi > r){
		segtree[i] += pending;
		return 0;
	}
	if (qi == l && qi == r){
		segtree[i] += pending;
		return segtree[i];
	}
	int mid = (l+r)/2;
	pending += segtree[i];
	segtree[i] = 0;
	int res = 0;
	res += query(segtree, 2*i+1, l, mid, qi, pending);
	res += query(segtree, 2*i+2, mid+1, r, qi, pending);

	return res;
}

void solve(){
	int n, m; cin >> n >> m;
	vector<int> adj[n+1];
	REP1(i, n-1){
		int u, v; cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	int size = log2(n)+1;
	vector< vector<int> > lift(n+1, vector<int>(size));

	vector<int> euler(2*n);
	vector<int> depth(n+1);
	vector<ii> positions(n+1); 

	vector<int> segtree(8*n, 0);
	int i = 0;
	dfs(1, adj, euler, depth, positions,  0, i, 1, lift);
	for (int i=1; i<size; ++i){
		for (int j=1; j<=n; ++j){
			lift[j][i] = lift[lift[j][i-1]][i-1];
		}
	}

	vector<int> lccount(n+1, 0);
	while (m--){
		int a, b; cin >> a >> b;
		int lc =  lca(a, b, positions, lift);
		lccount[lc]++;
		update(segtree, 0, 0, 2*n-1, positions[lc].first, positions[a].second - 1, 1, 0);
		update(segtree, 0, 0, 2*n-1, positions[lc].first, positions[b].second - 1, 1, 0);
	}
	for (int i=1; i<=n; ++i){
		cout << query(segtree, 0, 0, 2*n-1, positions[i].first, 0) - query(segtree, 0, 0, 2*n-1, positions[i].second, 0) - lccount[i] << endl;
	}
}
signed main(){
	cin.tie(NULL); ios_base::sync_with_stdio(false);
	// #ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
	// #endif
	solve();
	
	return 0;
}