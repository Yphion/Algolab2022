#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void solve(){
  
  int n, m, s, w;
  cin >> n >> m;
  
  vector<int> S;
  S.reserve(n);
  
  for(int i=0; i<n; ++i){
    cin >> s;
    S.push_back(s);
  }
  
  vector<int> W;
  W.reserve(m);
  
  for(int i=0; i<m; ++i){
    cin >> w;
    W.push_back(w);
  }
  
  sort(S.begin(), S.end(), greater<int>());
  
  sort(W.begin(), W.end(), greater<int>());
  
  int i=1; // box id
  int j=1; // friend id
  
  int k=0; // free power
  
  int count = 1;
  
  if (W[0] > S[0]){
    cout << "impossible" << endl;
    return;
  }
  
  while(i<m){
    
    if (k > 0){
      i += k;
      k = 0;
    } else {
      
      if (j < n){
        
        if (S[j] >= W[i]){
          k += count-1;
          j++;
          i++;
        } else {
          count++;
          k += j;
        }
        
      } else {
        count++;
        k += n;
      }
      
    }
    
  }
  
  cout << 3*count-1 << endl;
}

int main(){
  
  int t;
  
  cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
