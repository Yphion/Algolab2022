#include <iostream>
#include <vector>

using namespace std;

int maxval(int i, int j, vector<vector<int>> &dp){
  if(i==j){
    return dp[i][i];
  }
  
  if (j < i){
    return 0;
  }
  
  if (dp[i][j] != 0){
    return dp[i][j];
  }

  int val1 = dp[i][i] + min(maxval(i+2, j, dp), maxval(i+1, j-1, dp));
  int val2 = dp[j][j] + min(maxval(i, j-2, dp), maxval(i+1, j-1, dp));
  int res = max(val1, val2);
  dp[i][j] = res;
  return res;
}

void solve(){
  int n, tmp;
  
  cin >> n;
  
  vector<vector<int>> dp(n, vector<int>(n,0));
  
  for(int i=0; i<n; ++i){
    cin >> tmp;
    dp[i][i] = tmp;
  }
  
  int res = maxval(0, n-1, dp);
  cout << res << endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  
  int t;
  cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
