#include <iostream>
#include <string>
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

void solve() {
  
  int w, h;
  std::cin >> w >> h;
  
  std::string s;
  
  std::vector<std::vector<bool>> M(h+2, std::vector<bool>(w+2, false));
  
  int sum = 0;
  
  for(int i=0; i<h; ++i){
    std::cin >> s;
    
    for(int j=0; j<w; ++j){
      if (s[j] == '.'){
        sum++;
        M[i+1][j+1] = true;
      }
    }
  }
  
  graph G(w*h+2);
  edge_adder adder(G);
  
  int source = w*h;
  int sink = source + 1;
  
  for(int i=0; i<h; ++i){
    for(int j=0; j<w; ++j){
      
      if (i%2 == j%2){
        if (M[i+1][j+1]){
          adder.add_edge(source, i*w+j, 1);
          
          if (M[i][j+1]){
            adder.add_edge(i*w+j, (i-1)*w+j, 1);
          }
          
          if (M[i+1][j]){
            adder.add_edge(i*w+j, i*w+j-1, 1);
          }
          
          if (M[i+2][j+1]){
            adder.add_edge(i*w+j, (i+1)*w+j, 1);
          }
          
          if (M[i+1][j+2]){
            adder.add_edge(i*w+j, i*w+j+1, 1);
          }
        }
      } else {
        if (M[i+1][j+1]){
          adder.add_edge(i*w+j, sink, 1);
        }
      }
      
    }
  }

  long flow = boost::push_relabel_max_flow(G, source, sink);
  std::cout << (sum == 2*flow ? "yes" : "no") << std::endl;

}

int main() {
  int t;
  std::cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
