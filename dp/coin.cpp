#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;


signed main(){
	int n, x; cin >> n >> x;
	int a[n];
	for (int i=0; i<n; ++i) cin >> a[i];
	int dp[x+1];
	dp[0] = 0;
	for (int i=1; i<=x; ++i){
		dp[i] = MOD;
		for (int t=0; t<n; ++t){
			if (a[t]>i) continue;
			dp[i] = min(dp[i], 1+dp[i-a[t]]);
		}
	}
	cout << (dp[x]==MOD ? -1: dp[x]) << endl;
}