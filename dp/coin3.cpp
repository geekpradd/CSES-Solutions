#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;


signed main(){
	// #ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
	// #endif
	int n, x; cin >> n >> x;
	int a[n];
	for (int i=0; i<n; ++i) cin >> a[i];
	sort(a, a+n)
	int dp[x+1][n+1];
	dp[0][0] = 1;
	for (int i=1; i<=n; ++i)
	for (int i=1; i<=x; ++i){
		dp[i] = 0;
		for (int t=0; t<n; ++t){
			if (a[t]>i) continue;
			dp[i] = (dp[i] + dp[i-a[t]])%MOD;
		}
	}
	cout << dp[x] << endl;
}