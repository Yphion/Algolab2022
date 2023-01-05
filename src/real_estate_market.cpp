#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph;

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; 

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; 
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost; 
    w_map[rev_e] = -cost;
  }
};

void solve(){
  int n, m, s;
  std::cin >> n >> m >> s;
  
  graph G(s + m + n + 2);
  edge_adder adder(G);
  
  int property = s;
  int buyer = s + m;
  
  int source = s + m + n;
  int target = source + 1;
  
  for(int i=0; i<s; ++i){
    int tmp;
    std::cin >> tmp;
    adder.add_edge(source, i, tmp, 0);
  }
  
  for(int i=0; i<m; ++i){
    int tmp;
    std::cin >> tmp;
    adder.add_edge(tmp-1, property+i, 1, 0);
  }
  
  for(int i=0; i<n; ++i){
    adder.add_edge(buyer+i, target, 1, 0);
    for(int j=0; j<m; ++j){
      int tmp;
      std::cin >> tmp;
      adder.add_edge(property+j, buyer+i, 1, 100-tmp);
    }
  }

  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  boost::successive_shortest_path_nonnegative_weights(G, source, target);
  int cost = boost::find_flow_cost(G);
  
  int flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(source,G), G); e != eend; ++e) {
      flow += c_map[*e] - rc_map[*e];     
  }
  
  std::cout << flow << " " << (flow*100-cost) << std::endl;
  
}

int main(){
  int t;
  std::cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
