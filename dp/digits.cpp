#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;


signed main(){
	// #ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
	// #endif
	int n; cin >> n;
	int dp[n+1];
	dp[0] = 0;
	for (int i=1; i<=n; ++i){
		int copy = i;
		dp[i] = MOD;
		while (copy > 0){
			int digit = copy%10;
			if (i-digit>=0){
				dp[i] = min(dp[i], 1+dp[i-digit]);
			}
			copy = copy/10;
		}
	}
	cout << dp[n] << endl;
}