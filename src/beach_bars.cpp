#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(){
  int n, tmp;
  cin >> n;
  
  vector<int> x;
  x.reserve(n);
  
  for(int i=0; i<n; ++i){
    cin >> tmp;
    x.push_back(tmp);
  }
  
  sort(x.begin(), x.end(), less<int>());
  
  int curri = 0, currj = 0;
  int opt1 = -1, opt2 = 0;
  vector<int> cand;
  
  while(curri < n){
    
    if(curri > currj){
      currj++;
      continue;
    }
    
    int dist = x[currj]-x[curri];
    if(dist <= 200){
      int d1 = (dist+1)/2;
      int val = currj-curri+1; 
      bool add = false;
      
      
      if (val > opt1 || (val == opt1 && d1 < opt2)){
        opt1 = val;
        opt2 = d1;
        cand.clear();
        add = true;
      } else if (val == opt1 && d1 == opt2){
        add = true;
      }
      
      if (add){
        if (dist%2==0){
          cand.push_back(x[curri]+d1);
        } else {
          cand.push_back(x[curri]+d1-1);
          cand.push_back(x[curri]+d1);
        }
      }
      currj++;
      if(currj == n){
        break;
      }
    } else {
      curri++;
    }
    
    
  }
  
  cout << opt1 << " " << opt2 << endl;
  
  for(int y : cand){
    cout << y << " ";
  }
  cout << endl;
  
}

int main(){
  int t;
  cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
