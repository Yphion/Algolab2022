#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void solve(){
  
  int n, e, s, a, b;
  std::cin >> n >> e >> s >> a >> b;

  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  
  std::vector<edge_desc> es;
  std::vector<std::vector<int>> ews(e, std::vector<int>(0));
  
  for (int i=0; i<e; ++i){
    
    int u, v, tmp;
    
    std::cin >> u >> v;
    es.push_back(boost::add_edge(u, v, G).first); 
    
    ews[i].reserve(s);
    for(int j=0; j<s; ++j){
      std::cin >> tmp;
      ews[i].push_back(tmp);
    }
  }
  
  std::vector<int> hives;
  hives.reserve(s);
  for (int i=0; i<s; ++i){
    int tmp;
    std::cin >> tmp;
    hives.push_back(tmp);
  }
  
  std::map<edge_desc, int> ow;
  
  for(auto x : es){
    ow[x] = 1000000;
  }
  
  for(int i=0; i<s; ++i){
    
    for(int j=0; j<e; ++j){
      weights[es[j]] = ews[j][i];
    }
    
    std::vector<edge_desc> mst;
    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
    
    for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
      if (weights[*it] < ow[*it]){
        ow[*it] = weights[*it];
      }
    }
  }
  
  for(auto x : es){
    weights[x] = ow[x];
  }
  
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, a,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
  
  std::cout << dist_map[b] << std::endl;
}

int main(){
  int t;
  std::cin >> t;
  for (int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
