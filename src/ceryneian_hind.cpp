#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

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

void solve(){
  int n, m;
  std::cin >> n >> m;

  std::vector<int> conv;
  
  graph G(n+2);
  int source = n;
  int target = source + 1;
  edge_adder adder(G); 
  
  long maxin = 0;
  
  for(int i=0; i<n; ++i){
    long s;
    std::cin >> s;
    if (s > 0){
      maxin += s;
      adder.add_edge(source, i, s);
    } else if(s<0) {
      adder.add_edge(i, target, -s);
    }
  }
  
  long infty = 1000000;
  
  for(int i=0; i<m; ++i){
    int u,v;
    std::cin >> u >> v;
    adder.add_edge(u, v, infty);
  }
  
  long flow = boost::push_relabel_max_flow(G, source, target);
  
  long res = maxin-flow; 
  
  if (res <= 0){
    std::cout << "impossible" << std::endl;
  } else {
    std::cout << res << std::endl;
  }
}

int main(){
  int t;
  std::cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}