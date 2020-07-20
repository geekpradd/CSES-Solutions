#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;


signed main(){
	// #ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
	// #endif
	int n; cin >> n;
	bool grid[n][n];
	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j){
			char st; cin >> st;
			if (st=='*')
				grid[i][j] = 0;
			else
				grid[i][j] = 1;
		}
	}
	int dp[n][n];
	dp[n-1][n-1] = 1;
	if (grid[n-1][n-1] == 0){
		cout << 0 << endl;
		return 0;
	}
	for (int i=n-1; i>=0; --i){
		for (int j=n-1; j>=0; --j){
			if (j == n-1 && i==n-1) continue;
			dp[i][j] = 0;
			if (i!=n-1){
				dp[i][j] = (dp[i][j] + dp[i+1][j])%MOD;
			}
			if (j!=n-1){
				dp[i][j] = (dp[i][j]+ dp[i][j+1])%MOD;
			}

			if (grid[i][j] == 0)
				dp[i][j] = 0;
		}
	}
	cout << dp[0][0] << endl;
}