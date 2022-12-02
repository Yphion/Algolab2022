
#include <iostream>
#include <vector>

using namespace std;

void solve(){
  int n, tmp, sum = 0;
  cin >> n;
  
  vector<vector<int>> x, s;
  x.reserve(n);
  s.reserve(n+1);

  
  for(int i=0; i<n; ++i){
    
    x.push_back(vector<int>());
    s.push_back(vector<int>());

    x[i].reserve(n);
    s[i].reserve(n+1);
    
    for (int j=0; j<n; ++j){
      cin >> tmp;
      x[i].push_back(tmp);
      s[i].push_back(0);
    }
    
    s[i].push_back(0);
  }
  
  s.push_back(vector<int>());
  for (int i=0; i<=n; ++i){
    s[n].push_back(0);
  }
  
  for(int j=1; j<=n; ++j){
    s[0][j] = 0;
  }
  
  for(int i=0; i<=n; ++i){
    s[i][0] = 0;
  }
  for(int i=1; i<=n; ++i){
    
    for (int j=1; j<=n; ++j){
      
      s[i][j] = (s[i][j-1]+s[i-1][j]+s[i-1][j-1]+x[i-1][j-1])%2;
      
    }
    
  }
  
  
  
  for (int i=0; i<n; ++i){
    for (int j=i; j<n; ++j){
      int o=0, e=0;
      for (int h=1; h<=n; ++h){
        
        int y = (s[j+1][h]+s[i][h]+s[j+1][h-1]+s[i][h-1])%2;

        if (y%2 == 0){
          e = e + 1;
          o = o;
        } else {
          y = e;
          e = o;
          o = y + 1;
        }
        sum += e;
      }
    }
  }
  
  cout << sum << endl;
  
}

int main(){
  
  int t;
  cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
  
}
