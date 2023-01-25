#include <iostream>
#include <limits.h>

#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

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

void solve(){
  int n, m, a, s, c, d;
  std::cin >> n >> m >> a >> s >> c >> d;
  
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  
  
  for(int i=0; i<m; ++i){
    char w; int x, y, z;
    std::cin >> w >> x >> y >> z;
    
    edge_desc e;
    e = boost::add_edge(x, y, G).first; weights[e]=z;
    if(w == 'L'){
      e = boost::add_edge(y, x, G).first; weights[e]=z;
    }
  }
  
  std::vector<std::vector<int>> dist_maps(a,std::vector<int>(n));
  
  for (int i=0; i<a; ++i){
    int start;
    std::cin >> start;
    boost::dijkstra_shortest_paths(G, start, boost::distance_map(boost::make_iterator_property_map(dist_maps[i].begin(), boost::get(boost::vertex_index, G))));
  }
  
  std::vector<std::vector<int>> shelter_maps(a, std::vector<int>(s, 0));
  
  for(int i=0; i<s; ++i){
    int end;
    std::cin >> end;
    for(int j=0; j<a; ++j){
      shelter_maps[j][i] = dist_maps[j][end];
    }
  }
  
  int low = -1;
  int high = INT_MAX;
  
  while(low + 1 < high){
    int mid = (high + low)/2;
    
    graph G(a + c*s + 2);
    edge_adder adder(G);
    
    int source = a + c*s;
    int target = source + 1;
    
    for(int i=0; i<a; ++i){
      adder.add_edge(source, i, 1);
      
      for(int j=1; j<=c; ++j){
        for(int k=0; k<s; ++k){
          int val = shelter_maps[i][k];
          if (val <= mid - j*d)
            adder.add_edge(i, a+(j-1)*s+k, 1);
        }
      }
    }
    
    for(int i=0; i<c*s; ++i){
      adder.add_edge(a+i, target, 1);
    }
    
    long flow = boost::push_relabel_max_flow(G, source, target);
    if(flow == a){
      high = mid;
    } else {
      low = mid;
    }
  }
  
  std::cout << high << std::endl;
}

int main(){
  int t;
  std::cin >> t;
  while(t--) solve();
  return 0;
}
