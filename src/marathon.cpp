#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <tuple>
#include <limits.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; 
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

using namespace std;

typedef pair<int,int> P;
typedef priority_queue<P, vector<P>, greater<P>> Q;
typedef tuple<int,int,int> T;

void solve(){
  int n, m, s, f;
  cin >> n >> m >> s >> f;
  
  multimap<int, T> Adj;
  
  for(int i=0; i<m; ++i){
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    Adj.insert(pair<int,T>(a, T(b,c,d)));
    Adj.insert(pair<int,T>(b, T(a,c,d)));
  }
  
  Q q;
  q.push(P(0,s));

  vector<int> D(n, INT_MAX);
  D[s] = 0;
  vector<vector<int>> Preds(n, vector<int>()); 
  
  while(!q.empty()){
    P p = q.top();
    q.pop();
    if (p.first > D[p.second]){
      continue;
    }
    if(p.first > D[f]){
      break;
    }
    
    auto r = Adj.equal_range(p.second);
    for(auto i = r.first; i != r.second; ++i){
      int ind = get<0>(i->second);
      int d = p.first+get<2>(i->second);
      
      if(d < D[ind]){
        D[ind] = d;
        Preds[ind].clear();
        Preds[ind].push_back(p.second);
        q.push(P(d,ind));
      } else if (d == D[ind]){
        Preds[ind].push_back(p.second);
      }
    }
  }
  
  vector<bool> valid(n, false);
  queue<int> PQ;
  PQ.push(f);
  while(!PQ.empty()){
    int t = PQ.front();
    PQ.pop();
    
    if(valid[t]){
      continue;
    }
    valid[t] = true;
    for(int t2 : Preds[t]){
      PQ.push(t2);
    }
  }
  
  graph G(n);
  edge_adder adder(G);
  
  for(int i=0; i<n; ++i){
    if(valid[i]){
      int currd = D[i];
      auto r = Adj.equal_range(i);
      for(auto j = r.first; j != r.second; ++j){
        int ind = get<0>(j->second);
        int w = get<1>(j->second);
        int d = currd+get<2>(j->second);
        if(valid[ind] && D[ind] == d){
          adder.add_edge(i, ind, w);
        }
      }
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, s, f);
  cout << flow << endl;
}

int main(){
  int t;
  cin >> t;
  while(t--) solve();
  return 0;
}
