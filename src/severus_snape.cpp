#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


//k bottles
//1...i available
//h happyness required
long rec(int k, int i, int h, vector<vector<vector<long>>> &memo, vector<int> &Pi, vector<int> &Hi){
  
  if (k == 0 || i == 0){
    if (h > 0){
      return -1L;
    } else {
      return 0L;
    }
  }
  
  if (memo[k-1][i-1][h] > -2L){
    return memo[k-1][i-1][h];
  }
  
  long val1 = rec(k, i-1, h, memo, Pi, Hi);
  
  long val2 = rec(k-1, i-1, max(0,h-Hi[i-1]), memo, Pi, Hi);
  
  if (val2 > -1L){
    val2 += Pi[i-1];
  }
  
  long res = max(val1, val2);
  
  memo[k-1][i-1][h] = res;
  
  return res;
  
}

void solve(){
  
  int n, m, a, b, p, h, w, hi, pi, wi;
  
  cin >> n >> m >> a >> b >> p >> h >> w;
  
  vector<int> Pi;
  Pi.reserve(n);
  
  vector<int> Hi;
  Hi.reserve(n);
  
  for(int i=0; i<n; ++i){
    cin >> pi >> hi;
    Pi.push_back(pi);
    Hi.push_back(hi);
  }
  
  vector<long> Wi;
  Wi.reserve(m);
  for(int i=0; i<m; ++i){
    cin >> wi;
    Wi.push_back(wi);
  }

  sort(Wi.begin(), Wi.end(), greater<int>());
  
  vector<int> Wx;
  
  long wsum = 0L;
  int wit = 0;
  int ait = 0;

  while(wit <= m){
    if(wsum - ait*(long)a >= w && ait <= n){
      Wx.push_back(wit);
      ait++;
    } else {
      if (wit == m) break;
      wsum += Wi[wit++];
    }
  }
  
  vector<vector<vector<long>>> memo(n, vector<vector<long>>(n, vector<long>(h+1,-2L)));
  
  long out = -1L;
  
  for(long unsigned int i=1; i<Wx.size(); ++i){
    
    long bcount = Wx[i];
    long res = rec(i, n, h, memo, Pi, Hi);
    if(res - bcount*b >= p ){
      out = i + bcount;
      break;
    } 
    
  }
  
  cout << out << endl;
}

int main(){
  int t;
  cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
