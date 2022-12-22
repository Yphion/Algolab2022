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
  
  int h, w;
  std::cin >> h >> w;
  
  std::string s;
  std::cin >> s;
  
  std::vector<int> S(26,0);
  int n = s.size();
  
  for(int i=0; i<n; ++i){
    S[(int)s[i]-65]++;
  }
  
  std::vector<std::vector<int>> Sq(26, std::vector<int>(26, 0));
  
  std::vector<std::vector<int>> Sf(h, std::vector<int>(w,0));
  
  for(int i=0; i<h; ++i){
    std::cin >> s;
    for(int j=0; j<w; ++j){
      Sf[i][j] = (int)s[j]-65;
    }
  }
  
  for(int i=0; i<h; ++i){
    std::cin >> s;
    for(int j=0; j<w; ++j){
      int back = (int)s[j]-65;
      int front = Sf[i][w-1-j];
      
      Sq[front][back]++;
    }
  }
  
  int offset = 26*26;
  int source = offset + 26;
  int target = source + 1;
  
  graph G(27*26+2);
  edge_adder adder(G);
  
  int k=0;
  for(int i=0; i<26; ++i){
    for (int j=0; j<26; ++j, ++k){
      int val = Sq[i][j];
      adder.add_edge(source, k, val);
      adder.add_edge(k, offset+i, val);
      adder.add_edge(k, offset+j, val);
    }
  }
  
  for(int i=0; i<26; ++i){
    adder.add_edge(offset+i, target, S[i]);
  }
  
  long flow = boost::push_relabel_max_flow(G, source, target);
  std::cout << (flow == n ? "Yes" : "No") << std::endl;
}

int main() {
  int t;
  std::cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
