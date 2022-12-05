#include <iostream>
#include <vector>
#include <map>

void solve(){
  
  int n, w, tmp;
  long k;
  
  std::cin >> n >> k >> w;
  
  std::vector<int> c;
  c.reserve(n);
  for(int i=0; i<n; ++i){
    std::cin >> tmp;
    c.push_back(tmp);

  }
  
  std::vector<std::vector<int>> dp(w, std::vector<int>(0));
  std::vector<std::vector<long>> psum(w, std::vector<long>(1,c[0]));
  
  for(int i=0; i<w; ++i){
    int l;
    std::cin >> l;
    
    for(int j=0; j<l; ++j){
      std::cin >> tmp;
      dp[i].push_back(c[tmp]);

    }
  }
  
  for(int i=0; i<w; ++i){
    int l = dp[i].size();
    for(int j=1; j<l; ++j){
      psum[i].push_back(psum[i][j-1]+dp[i][j]);
    }
  }

  int mx = 0;
  
  
  
  for(int i=0; i<w; ++i){
    
    int curri = 0;
    int currj = 0;
    
    int l = dp[i].size();

    while (currj < l){
      
      if (curri > currj){
        currj++;
        continue;
      }
      
      long val = psum[i][currj]-psum[i][curri]+dp[i][curri];
      if (val == k){
        if (currj-curri+1 > mx){
          mx = currj-curri+1;
        }
        curri++;
        currj++;
      } else if (val < k){
        currj++;
      } else {
        curri++;
      }
      
    }
  }
  
  std::map<int, std::vector<int>> mp;
  
  for(int i=0; i<w; ++i){
    int l = dp[i].size();
    for(int j=1; j<l; ++j){
      if (psum[i][j]>=k){
        break;
      } 
      
      if(mp.find(psum[i][j]) != mp.end()){
        std::vector<int> rs = mp[psum[i][j]];
        
        if(rs.size() == 4){
          
          if(j > rs[0]){
            rs[2] = rs[0];
            rs[3] = rs[1];
            
            rs[0] = j;
            rs[1] = i;
          } else if(j > rs[2]){
            rs[2] = j;
            rs[3] = i;
          }
          
        } else if (rs.size() == 2){
          if(j > rs[0]){
            rs.push_back(rs[0]);
            rs.push_back(rs[1]);
            
            rs[0] = j;
            rs[1] = i;
          } else {
            rs[2] = j;
            rs[3] = i;
          }
        }
      } else {
        std::vector<int> rs;
        rs.push_back(j);
        rs.push_back(i);
        
        mp[psum[i][j]] = rs;
      }
    }
  }
  
  for(int i=0; i<w; ++i){
    
    int l = dp[i].size();
    for (int j=1; j<l; ++j){
      int preval = k-psum[i][j]+c[0];
      if(mp.find(preval) != mp.end()){
        std::vector<int> rs = mp[preval];
        int pp = 0;
        if(rs.size() == 4){
          if(rs[3] != i){
            pp = j + rs[2]+1; 
          }
        }
        if(rs.size() >= 2){
          if(rs[1] != i){
            pp = j + rs[0]+1;
          }
        } 
        if(pp > mx){
          mx = pp;
        }
      }
    }
    
  }

  std::cout << mx << std::endl;

}


int main(){
  
  std::ios_base::sync_with_stdio(false);
  
  int t;
  std::cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
