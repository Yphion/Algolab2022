#include <vector>
#include <iostream>

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
  int n, m, k, c;
  std::cin >> m >> n >> k >> c;
  
  graph G(2*m*n+2);
  
  int offset = m*n;
  int source = 2*offset;
  int target = source + 1;
  
  edge_adder adder(G);
  
  for(int i=0; i<k; ++i){
    int x, y;
    std::cin >> x >> y;
    adder.add_edge(source, y*m + x, 1);
  }
  
  if (c <= 0){
    std::cout << 0 << std::endl;
    return;
  }
  
  for(int i=0; i<offset; ++i){
    adder.add_edge(i, offset+i, c);
  }
  
  for(int i=0; i<n; ++i){
    for(int j=0; j<m; ++j){
      int pos = i*m+j;
      if(i>0){
        adder.add_edge(offset+pos, pos-m, 1);
      } else {
        adder.add_edge(offset+pos, target, 1);
      }
      if(i<n-1){
        adder.add_edge(offset+pos, pos+m, 1);
      } else {
        adder.add_edge(offset+pos, target, 1);
      }
      if(j>0){
        adder.add_edge(offset+pos, pos-1, 1);
      } else {
        adder.add_edge(offset+pos, target, 1);
      }
      if(j<m-1){
        adder.add_edge(offset+pos, pos+1, 1);
      } else {
        adder.add_edge(offset+pos, target, 1);
      }
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, source, target);
  
  std::cout << flow << std::endl;
  
}


int main(){
  int t;
  std::cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
