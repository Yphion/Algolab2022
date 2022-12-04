#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor    vertex_desc;
typedef boost::graph_traits<graph>::edge_descriptor    edge_desc; 
typedef boost::graph_traits<graph>::edge_iterator    ei, ei_end;

void solve(){
  int n, m, u, v;
  std::cin >> n >> m;
  
  graph G(n);
  
  std::vector<edge_desc> es;
  
  es.reserve(m);
  for(int i=0; i<m; ++i){
    std::cin >> u >> v;
    es.push_back(boost::add_edge(u, v, G).first);
  }

  std::map<edge_desc, int> component_map;
  auto component = boost::make_assoc_property_map(component_map);
  
  int ncc = boost::biconnected_components(G, component); 

  
  std::vector<std::vector<edge_desc>> component_vertices(ncc);
  for (auto x : es){
    component_vertices[component[x]].push_back(x);
  }

  int res = 0;
  std::vector<std::pair<int,int>> rel;
  for(int i=0; i<ncc; ++i){
    if (component_vertices[i].size() == 1){
      res++;
      
      int u = boost::source(component_vertices[i][0], G);
      int v = boost::target(component_vertices[i][0], G);
      if (v < u){
        std::swap(u,v);
      }
      rel.push_back(std::pair<int,int>(u, v));
    }
  }
  
  std::sort(rel.begin(), rel.end());
  
  std::cout << res << std::endl;
  
  for(auto x : rel){
    std::cout << x.first << " " << x.second << std::endl;
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
