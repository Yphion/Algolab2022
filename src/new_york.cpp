#include <iostream>
#include <set>
#include <vector>

using namespace std;

void rec(const vector<vector<int>> &adj, const vector<int> &H, multiset<int> &temps, vector<int> &stack, vector<bool> &feasible, int m, int k, int node){
  stack.push_back(node);
  temps.insert(H[node]);
  
  int pretemp = -1;
  if(temps.size() > m){
    pretemp = *(temps.lower_bound(H[stack[stack.size()-m-1]]));
    temps.erase(temps.lower_bound(H[stack[stack.size()-m-1]]));
  }

  if(temps.size() >= m) {
    if(*(temps.rbegin())- *(temps.begin()) <= k){
      feasible[stack[stack.size()-m]] = true;
    }
  }
  
  for(int x : adj[node]){
    rec(adj, H, temps, stack, feasible, m, k, x);
  }

  
  temps.erase(temps.lower_bound(H[node]));
  if(pretemp > -1){
    temps.insert(pretemp);
  }
  stack.pop_back();
    
}

void solve(){
  int n, m, k;
  cin >> n >> m >> k;
  
  vector<int> H;
  H.reserve(n);
  for(int i=0; i<n; ++i){
    int h;
    cin >> h;
    H.push_back(h);
  }
  
  vector<vector<int>> adj(n, vector<int>());
  
  for(int i=1; i<n; i++){
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }
  
  multiset<int> temps;
  vector<int> stack;
  vector<bool> feasible(n, false);
  
  rec(adj, H, temps, stack, feasible, m, k, 0);
  
  bool out = false;
  for(int i=0; i<n; ++i){
    if(feasible[i]){
      cout << i << " ";
      out = true;
    }
  }
  if (out){
    cout << endl;
  } else {
    cout << "Abort mission" << endl;
  }
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
