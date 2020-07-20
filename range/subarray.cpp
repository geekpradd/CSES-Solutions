#include <bits/stdc++.h>
#define int long long
#define MOD 1000000007
using namespace std;
#define DUMP(a) \
    do { std::cout << "[" << #a " = " << (a) << "]" <<  std::endl; } while(false)

struct dat {
	int ans, sum, prefix, suffix;
};

void build_tree(vector< dat >& segtree, int a[], int i, int l, int r){

	if (l == r){
		segtree[i] = {max(a[l], 0LL), a[l], max(a[l], 0LL), max(a[l], 0LL)};
		return;
	}
	int mid = (l+r)/2;
	build_tree(segtree, a, 2*i+1, l, mid);
	build_tree(segtree, a, 2*i+2, mid+1, r);
	dat left = segtree[2*i+1];
	dat right = segtree[2*i+2];

	int sum = left.sum + right.sum;
	int prefix = max(left.prefix, left.sum + right.prefix);
	int suffix = max(right.suffix, right.sum + left.suffix);
	int ans = max(left.ans, max(right.ans, left.suffix + right.prefix));
	segtree[i] = {ans, sum, prefix, suffix};

	return;
}

void update(vector<dat>& segtree, int a[], int i, int l, int r, int position, int x){
	if (position < l || position > r){
		return;
	}
	if (position == l && position == r){
		segtree[i] = {max(x, 0LL), x, max(x, 0LL), max(x, 0LL)};
		return;
	}
	int mid = (l+r)/2;
	update(segtree, a, 2*i+1, l, mid, position, x);
	update(segtree, a, 2*i+2, mid+1, r, position, x);
	dat left = segtree[2*i+1];
	dat right = segtree[2*i+2];
	int sum = left.sum + right.sum;
	int prefix = max(left.prefix, left.sum + right.prefix);
	int suffix = max(right.suffix, right.sum + left.suffix);
	int ans = max(left.ans, max(right.ans, left.suffix + right.prefix));
	segtree[i] = {ans, sum, prefix, suffix};

}
signed main(){
	// #ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
	// #endif
	int n, q; cin >> n >> q;

	int size = 4*n;
	int a[n];
	for (int i=0; i<n; ++i){
		cin >> a[i];
	}
	vector<dat> segtree(size);

	build_tree(segtree, a, 0, 0, n-1);
	while (q--){
		int k, x; cin >> k >> x;
		k--;
		update(segtree, a, 0, 0, n-1, k, x);
		cout << segtree[0].ans << endl;
	}

	return 0;
	
}