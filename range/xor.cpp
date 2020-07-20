#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;


signed main(){
	// #ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
	// #endif
	int n, q; cin >> n >> q;
	int size = log2(n)+1;
	int a[n][size];
	for (int i=0; i<n; ++i){
		cin >> a[i][0];
	}
	for (int i=1; i<size; ++i){
		for (int j=0; j<n; ++j){
			int mid = j + (1 << (i-1));
			int end = j + (1 << i) - 1;
			if (end < n){
				a[j][i] = a[j][i-1]^a[mid][i-1];
			}
		}
	}
	while (q--){
		int l, r; cin >> l >> r;
		l--; r--;
		int gap = (r-l+1);
		int iter = 1;
		int result = 0;
		int count = 0;
		while (gap > 0){
			if (gap&iter){
				result = result ^ a[l][count];
				l = l + iter;
				gap -= iter;
			}

			iter = iter << 1;
			count++;
		}

		cout << result << endl;
	}
	
}