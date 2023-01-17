#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>

using namespace std;

void solve(){
  int n, k, m;
  cin >> n >> k >> m;
  
  vector<int> X;
  X.reserve(n);
  
  for(int i=0; i<n; ++i){
    int x;
    cin >> x;
    X.push_back(x+1);
  }
  
  vector<vector<map<string,int>>> DP(n+1, vector<map<string,int>>(23, map<string,int>()));
  
  string init = "----";
  for(int i=0; i<4; ++i){
    init[i] = 0;
  }
  
  DP[0][11][init] = 0;
  
  for(int i=1; i<=n; ++i){
    
    int nxt = X[i-1];
    
    for(int j=0; j<23; ++j){
      
      for(pair<string,int> p : DP[i-1][j]){
        
        //south
        
        int pre1 = p.first[0];
        int pre2 = p.first[1];
        
        set<int> Q;
        
        if(pre1 != 0){
          Q.insert(pre1);
        }
        
        if(pre2 != 0 && m == 3){
          Q.insert(pre2);
        }
        
        Q.insert(nxt);
        
        int score = Q.size()*1000 - (1<<abs(j-12));
        if(score >= 0){
          
          score += p.second;
          
          init[0] = nxt;
          init[1] = pre1;
          init[2] = p.first[2];
          init[3] = p.first[3];
          
          if (score >= DP[i][j-1][init]){
            DP[i][j-1][init] = score;
          }
        }

        //north
        
        pre1 = p.first[2];
        pre2 = p.first[3];
        
        Q.clear();
        
        if(pre1 != 0){
          Q.insert(pre1);
        }
        
        if(pre2 != 0 && m == 3){
          Q.insert(pre2);
        }
        
        Q.insert(nxt);
        
        score = Q.size()*1000 - (1<<abs(j-10));
        if(score >= 0){
          
          score += p.second;
          
          init[0] = p.first[0];
          init[1] = p.first[1];
          init[2] = nxt;
          init[3] = pre1;
          
          if (score >= DP[i][j+1][init]){
            DP[i][j+1][init] = score;
          }
          
        }
        
      }
      
    }
    
    
  }
  
  
  int res = 0;
  for(int i=0; i<23; ++i){
    for(auto p : DP[n][i]){
      if(p.second > res){
        res = p.second;
      }
    }
  }
  
  cout << res << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
