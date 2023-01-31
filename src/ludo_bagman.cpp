#include <iostream>
#include <map>
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
  int e, w, m, d, p, l;
  std::cin >> e >> w >> m >> d >> p >> l;

  if (p - e*l < 0 || p - w*l < 0) {
    std::cout << "No schedule!" << std::endl;
    int tmp;
    for (int i=0; i<3*(m+d); ++i)
      std::cin >> tmp;
    return;
  }

  const int N = 2*(e+w)+6;
  
  graph G(N);
  edge_adder adder(G);  
  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  const int src = 2*(e+w);
  const int tgt = src + 1;
  const int xsrc = tgt + 1;
  const int xtgt = xsrc + 1;
  const int ysrc = xtgt + 1;
  const int ytgt = ysrc + 1;
  
  const int o1 = e+w;
  const int o2 = 2*e+w;
  
  for(int i=0; i<m; ++i){
    int u, v, r;
    std::cin >> u >> v >> r;
    adder.add_edge(u, e + v, 1, r);
  }
  
  
  std::map<int,int> dmap;
  for(int i=0; i<d; ++i){
    int u, v, r;
    std::cin >> u >> v >> r;
    if(dmap.count(r)){
      dmap[r]++;
    } else {
      dmap[r] = 1;
    }
  }
  
  for(auto const &x : dmap){
    adder.add_edge(ysrc, ytgt, x.second, x.first);
  }
  
  for(int i=0; i<e; ++i){
    adder.add_edge(src, i, l, 0);
    adder.add_edge(xsrc, i, p, 0);
  }
  
  for(int i=0; i<w; ++i){
    adder.add_edge(e+i, tgt, l, 0);
    adder.add_edge(e+i, xtgt, p, 0);
  }
  
  adder.add_edge(src, xsrc, p-e*l, 0);
  adder.add_edge(xtgt, tgt, p-w*l, 0);
  adder.add_edge(xsrc, ysrc, p-e*l, 0);
  adder.add_edge(ytgt, xtgt, p-e*l, 0);
  
  boost::successive_shortest_path_nonnegative_weights(G, src, tgt);
  long cost = boost::find_flow_cost(G);

  long flow = 0;
  out_edge_it ed, eend;
  for(boost::tie(ed, eend) = boost::out_edges(boost::vertex(src,G), G); ed != eend; ++ed) {
      flow += c_map[*ed] - rc_map[*ed];     
  }
  
  if (flow == p){
    std::cout << cost << std::endl;
  } else {
    std::cout << "No schedule!" << std::endl;
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
