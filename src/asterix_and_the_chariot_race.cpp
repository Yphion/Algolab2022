#include <iostream>
#include <vector>
#include <queue> 

using namespace std;

long rec(vector<vector<long>> &memo, const vector<vector<int>> &B, const vector<int> &C, int node, int take){
  if(memo[node][take] >= 0){
    return memo[node][take];
  }
  
  long res;
  if(take == 1){ //you have to take it
    res = C[node];
    for(const int x: B[node]){
      res += rec(memo, B, C, x, 2);
    }
  } else if (take == 2) { // covered by parent
    res = rec(memo, B, C, node, 1);
    long alt = 0;
    for(const int x: B[node]){
      alt += rec(memo, B, C, x, 0);
    }
    if(alt < res){
      res = alt;
    }
  } else { //you may take it
    res = rec(memo, B, C, node, 1);
    if(B[node].size()){
      long altsum = 0;
      for(const int x: B[node]){
        altsum += rec(memo, B, C, x, 0);
      }

      for(const int x: B[node]){
        long opt = altsum - rec(memo, B, C, x, 0) + rec(memo, B, C, x, 1);
        if(opt < res){
          res = opt;
        }
      }

    }
  }
  
  memo[node][take] = res;
  return res;
}

void solve(){
  int n;
  cin >> n;
  
  vector<vector<int>> A(n, vector<int>());
  
  for(int i=1; i<n; ++i){
    int x,y;
    cin >> x >> y;
    A[x].push_back(y);
    A[y].push_back(x);
  }
  
  vector<int> C;
  for(int i=0; i<n; ++i){
    int c;
    cin >> c;
    C.push_back(c);
  }
  
  vector<int> D(n, n);
  
  vector<vector<int>> B(n, vector<int>());
  
  queue<int> Q;
  Q.push(0);
  D[0] = 0;
  
  while(Q.size()){
    int q = Q.front();
    Q.pop();
    
    for(int x : A[q]){
      if(D[x] == n){
        B[q].push_back(x);
        D[x] = D[q]+1;
        Q.push(x);
      }
    }
  }
  
  vector<vector<long>> memo(n, vector<long>(3,-1));
  long val = rec(memo, B, C, 0, 0);
  cout << val << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while(t--) solve();
  return 0;
}
