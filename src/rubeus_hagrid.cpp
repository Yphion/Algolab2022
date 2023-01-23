#include <iostream>
#include <vector>
#include <algorithm>

struct Chamber {
  int index;
  int count;
  int length;
  long weight; 
  
  Chamber(int i, int c, int l, long w) : index(i), count(c), length(l), weight(w) {}

};

bool operator < (const Chamber& c1, const Chamber& c2) {
  return (c1.weight*c2.count < c2.weight*c1.count);
}


void prerec(std::vector<std::vector<Chamber>> &adj, Chamber &c){
  for(int i=0; i<adj[c.index].size(); ++i){
    Chamber &d = (adj[c.index][i]);
    prerec(adj, d);
    c.count += d.count;
    c.weight += d.weight;
  }
}

long rec(std::vector<std::vector<Chamber>> &adj, std::vector<int> &G, Chamber c, int t){
  long res = 0;
  if (c.index != 0) res = G[c.index-1]-t;
  if(adj[c.index].size() == 0){
    return res;
  } 
  sort(adj[c.index].begin(), adj[c.index].end());
  for(Chamber d : adj[c.index]){

    res += rec(adj, G, d, t+d.length);
    t += 2*d.weight;
  }
  return res;
  
}

void solve(){
  int n;
  std::cin >> n;
  
  std::vector<int> G;
  G.reserve(n);
  
  for(int i=0; i<n; ++i){
    int g;
    std::cin >> g;
    G.push_back(g);
  }
  
  Chamber init(0, 0, 0, 0);
  std::vector<std::vector<Chamber>> adj(n+1, std::vector<Chamber>());
  for(int i=0; i<n; ++i){
    int u, v, l;
    std::cin >> u >> v >> l;
    adj[u].push_back(Chamber(v,1,l,l));
  }
  
  prerec(adj, init);
  
  std::cout << rec(adj, G, init, 0) <<std::endl;
  
}

int main(){
  int t;
  std::cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
