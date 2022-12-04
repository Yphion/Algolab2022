#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void solve(){
  
  int n, c, f, inc=0;
  std::cin >> n >> c >> f;
  
  std::map<std::string,int> m;
  
  std::vector<std::vector<int>> q(n, std::vector<int>());
  
  
  std::string tmp;
  
  for (int i=0; i<n; ++i){
    q[i].reserve(c);
    for (int j=0; j<c; ++j){
      std::cin >> tmp;
      if(m.find(tmp) == m.end()){
        m[tmp] = inc++;
      } 
      q[i].push_back(m[tmp]);
    }
  }
  
  for (int i=0; i<n; ++i){
    std::sort(q[i].begin(), q[i].end(), std::less<int>());
  }
  
  weighted_graph G(n);
  
  for(int i=0; i<n; ++i){
    for(int j=i+1; j<n; ++j){
      
      int ct = 0;
      
      int k=0;
      int l=0;
      
      while( ct <= f){
        
        if(k == c || l == c){
          break;
        }
        
        if (q[i][k] == q[j][l]){
          ct++;
          k++;
          l++;
        } else if (q[i][k] > q[j][l]){
          l++;
        } else {
          k++;
        }
        
      }
      
      if ( ct > f ){
        boost::add_edge(i, j, G);
      }
    }
  }
  
  
  std::vector<vertex_desc> mate_map(n); 
  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

  std::cout << (matching_size==n/2 ? "not optimal" : "optimal") << std::endl;
}

int main(){
  int t;
  std::cin >> t;
  
  for(int i=0; i<t; ++i){
    
    solve();
    
  }
  
  return 0;
}
