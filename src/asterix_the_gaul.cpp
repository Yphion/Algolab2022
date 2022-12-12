#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

bool check(int n, long D, long T, long ss, vector<long> &dx, vector<long> &tx){
  
  vector<pair<long,long>> Qx;
  vector<pair<long,long>> Qy;
  
  int mid = n/2;
  
  for (int i=0; i<2; ++i){
    int begin = 0;
    int end = mid;
    
    if (i==1){
      begin = mid;
      end = n-mid;
    }
    
    for (int s = 0; s < 1<<end; ++s) { // Iterate through all subsets
      long tt = 0;
      long dd = 0;
      for (int i = 0; i < end; ++i) {
        if (s & 1<<i) {
          dd += dx[begin+i] + ss; // If i-th element in subset
          tt += tx[begin+i];
        }
      }
      if (tt < T) {
        if (i == 0){
          Qx.push_back(pair<long,long>(tt,dd));
        } else {
          Qy.push_back(pair<long,long>(tt,dd));
        }
      }
    }
  }
  
  sort(Qy.begin(), Qy.end());
  
  map<long,long> maxQy;
  long prev = -1L;
  
  for(auto x : Qy){
    if(x.second > prev){
      maxQy[-x.first] = x.second;
      prev = x.second;
    }
  }
  
  for(auto x : Qx){
    
    auto yd = maxQy.upper_bound(x.first-T);
    long plus = 0;
    if(yd != maxQy.end()){
      plus = yd->second;
    }
    
    if (plus + x.second >= D){
      return true;
    }
  }
  
  return false;
}

void solve(){
  int n, m;
  long D, T;
  
  cin >> n >> m >> D >> T;
  
  long d, t;
  
  vector<long> dx;
  vector<long> tx;
  dx.reserve(n);
  tx.reserve(n);
  
  for(int i=0; i<n; ++i){
    cin >> d >> t;
    dx.push_back(d);
    tx.push_back(t);
  }
  
  vector<long> sx;
  sx.reserve(m+1);
  sx.push_back(0L);
  
  for (int i=0; i<m; ++i){
    cin >> d;
    sx.push_back(d);
  }
  
  int curri = -1;
  int currj = m+1;
  
  while (currj-curri > 1){
    int mid = (currj+curri)/2;
    if (check(n, D, T, sx[mid], dx, tx)){
      currj = mid;
    } else {
      curri = mid;
    }
  }
  
  if (currj == m+1){
    cout << "Panoramix captured" << endl;
  } else {
    cout << currj << endl;
  }
}

int main(){
  int t;
  ios_base::sync_with_stdio(false);
  cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
