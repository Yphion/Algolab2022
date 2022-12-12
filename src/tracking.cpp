#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;

void solve(){
  int n, m, k, x, y;
  std::cin >> n >> m >> k >> x >> y;

  weighted_graph G(n*(k+1));
  weight_map weights = boost::get(boost::edge_weight, G);
  
  int a, b, c, d;
  
  for(int i=0; i<m; ++i){
    std::cin >> a >> b >> c >> d;
    
    for(int i=0; i<=k; ++i){
        edge_desc e;
        int bnew, anew;
        if(d == 1 && i < k){
          bnew = (i+1)*n+b;
          anew = (i+1)*n+a;
          e = boost::add_edge(i*n+a, bnew, G).first; weights[e]=c;
          e = boost::add_edge(anew, i*n+b, G).first; weights[e]=c;
          continue;
        } else {
          bnew = (i*n)+b;
          anew = (i*n)+a;
        }
        
        auto e2 = edge(i*n+a, bnew, G);
        if (e2.second) {
          if (weights[e2.first]<c){

          } else {
            weights[e2.first] = c;
          }
          continue;
        }
        
        e = boost::add_edge(i*n+a, bnew, G).first; weights[e]=c;
    }
  }
  
  std::vector<int> dist_map(n*(k+1));
  
  boost::dijkstra_shortest_paths(G, x,
  boost::distance_map(boost::make_iterator_property_map(
    dist_map.begin(), boost::get(boost::vertex_index, G))));
  
  std::cout << dist_map[n*k+y] << std::endl;
}


int main(){
  int t;
  std::cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
