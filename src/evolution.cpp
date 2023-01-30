#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

void solve(){
  int n, q;
  cin >> n >> q;
  
  
  map<string,int> s2i;
  vector<string> i2s;
  vector<int> A;
  
  int old = -1;
  int root = 0;
  
  for(int i=0; i<n; ++i){
    string s;
    int a;
    cin >> s >> a;
    
    if(a > old){
      old = a;
      root = i2s.size();
    }
    
    s2i[s] = i2s.size();
    i2s.push_back(s);
    A.push_back(a);
  }
  
  vector<vector<int>> B(n, vector<int>());
  vector<vector<int>> R(n, vector<int>());
  
  for(int i=1; i<n; ++i){
    string s, p; 
    cin >> s >> p;
    int i1 = s2i[s];
    int i2 = s2i[p];
    B[i2].push_back(i1);
    R[i1].push_back(i2);
  }
  
  vector<int> D(n, 0);
  
  queue<int> Q;
  Q.push(root);
  
  while(Q.size()){
    int q = Q.front();
    Q.pop();
    
    for(int x : B[q]){
      D[x] = D[q]+1;
      Q.push(x);
    }
  }
  
  int step = 2;
  unsigned int si = 1;
  while(step < n){
    for(int i=0; i<n; ++i){
      if(R[i].size() >= si){
        int im = R[i].back();
        if(R[im].size() >= si){
          R[i].push_back(R[im][si-1]);
        }
      }
    }
    
    si++;
    step*=2;
  }
  
  for(int i=0; i<q; ++i){
    string s;
    int b;
    cin >> s >> b;
    int i1 = s2i[s];
    
    if(b >= A[root]){
      cout << i2s[root] << " ";
      continue;
    }
    
    if(b <= A[i1]){
      cout << i2s[i1] << " ";
      continue;
    }
    
    int high = root;
    int low = i1;
    int d = D[i1];
    unsigned int step = R[i1].size()-1;
    while(d > 1){
      int cand;
      if(R[low].size() > step){
        cand = R[low][step];
      } else {
        cand = R[low].back();
      }
      
      if(A[cand] <= b){
        low = cand;
        d = D[low]-D[high];
        step = max(0u, step-1);
      } else {
        high = cand;
        d = D[low]-D[high];
        step = max(0u, step-1);
      }
    }
    
    cout << i2s[low] << " ";
  }
  
  cout << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; 
  cin >> t;
  while(t--) solve();
  return 0;
}
