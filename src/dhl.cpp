#include <iostream>
#include <vector>

using namespace std;

long rec(vector<vector<vector<int>>> &memo, vector<int> &A, vector<int> &B, int s, int i, int j){
  
  if(i < 0 || j < 0){
    return -1;
  }
  
  if (memo[s][i][j] > -2){
    return memo[s][i][j];
  }
  

  if (s==0 && i == 0){
    long sum = 0L;
    for(int k=j; k>=0; k--){
      sum += B[k];
    }
    sum *= A[0];
    memo[s][i][j] = sum;
    return sum;
  }
  
  if (s==1 && j==0){
    long sum = 0L;
    for(int k=i; k>=0; k--){
      sum += A[k];
    }
    sum *= B[0];
    memo[s][i][j] = sum;
    return sum;
  }
  
  //default
  long res = A[i]*B[j];
  
  long opt = -2;
  
  
  //accept and move on
  long alt = rec(memo, A, B, 0, i-1, j-1);
  if(alt > -1){
    alt += res;
    if(alt < opt || opt == -2){
      opt = alt;
    }
  }
  
  alt = rec(memo, A, B, 1, i-1, j-1);
  if(alt > -1){
    alt += res;
    if(alt < opt || opt == -2){
      opt = alt;
    }
  }
  
  //take more s
  if(s==0 && i > 0){
    long sub = rec(memo, A, B, s, i-1, j);
    if(sub > -1){
      sub += res;
      if(sub < opt || opt==-2){
        opt = sub;
      }
    }
  }
  
  if(s==1 && j > 0){
    long sub = rec(memo, A, B, s, i, j-1);
    if(sub > -1){
      sub += res;
      if(sub < opt || opt==-2){
        opt = sub;
      }
    }
  }
  

  
  memo[s][i][j] = opt;
  return opt;
}

void solve(){
  int n;
  cin >> n;
  
  vector<int> A;
  A.reserve(n);
  for(int i=0; i<n; ++i){
    int a;
    cin >> a;
    A.push_back(a-1);
  }
  
  vector<int> B;
  B.reserve(n);
  for(int i=0; i<n; ++i){
    int b;
    cin >> b;
    B.push_back(b-1);
  }
  
  vector<vector<vector<int>>> memo(2, vector<vector<int>>(n, vector<int>(n, -2)));
  
  cout << min(rec(memo, A, B, 0, n-1, n-1), rec(memo, A, B, 1, n-1, n-1)) << endl;
  
}

int main(){
  int t;
  cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
