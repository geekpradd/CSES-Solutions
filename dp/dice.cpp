#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;


signed main(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	#endif
	int n; cin >> n;
	int dp[n+1];
	dp[0] = 1;
	for (int i=1; i<=n; ++i){
		dp[i] = 0;
		for (int t=1; t<=6; ++t){
			if ((i-t)<0) continue;
			dp[i] = (dp[i]+dp[i-t])%MOD;
		}
	}
	cout << dp[n] << endl;
}