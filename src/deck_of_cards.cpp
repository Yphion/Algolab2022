
#include <iostream>
#include <vector>

using namespace std;

void solve(){
  int n, k, tmp;
  cin >> n >> k;
  
  vector<int> x, s;
  x.reserve(n);
  s.reserve(n+1);
  s.push_back(0);
  for (int i=0; i<n; ++i){
    cin >> tmp;
    x.push_back(tmp);
    s.push_back(tmp+s[i]);
  }

  int curri=0, currj=1;
  int opti = 0, optj=n;
  int opt = 1 << 30;
  int minj = 1;
  while(curri < n){
    int tsum = s[currj]-s[curri];
    if( abs(tsum - k) < opt){
      opti = curri;
      optj = currj;
      opt = abs(s[currj]-s[curri] - k);
    } 
      
    if (tsum < k){
      minj = currj;
      currj++;
      if (currj > n){
        break;
      }
    } else {
      curri++;
      currj = minj;
    }
  }
  
  cout << opti << " " << optj-1 << endl;
  
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
