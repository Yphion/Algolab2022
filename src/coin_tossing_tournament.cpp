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

void solve() {
  
  int n, m, a, b, c;
  std::cin >> n >> m;
  
  std::vector<int> S(n, 0);
  std::vector<std::pair<int,int>> edx; 
  
  for(int i=0; i<m; ++i){
    std::cin >> a >> b >> c;
    if (c == 0){
      edx.push_back(std::pair<int,int>(a,b));
    } else if(c == 1) {
      S[a]++;
    } else {
      S[b]++;
    }
  }
  
  m = edx.size();
  
  graph G(2+n+m);
  
  edge_adder adder(G);
  
  int source = m+n;
  int sink = m+n+1;
  
  for(int i=0; i<m; ++i){
    adder.add_edge(source, i, 1);
    adder.add_edge(i, m+edx[i].first, 1);
    adder.add_edge(i, m+edx[i].second, 1);
  }
  
  long sum = 0;
  
  bool res = true;
  
  for(int i=0; i<n; ++i){
    std::cin >> a;
    adder.add_edge(m+i, sink, a-S[i]);
    sum += a-S[i];
    if (a-S[i] < 0){
      res = false;
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, source, sink);
  std::cout << (res && (flow == sum) && (flow == m) ? "yes" : "no") << std::endl;
  
}

int main() {
  
  int t;
  std::cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }

  return 0;
}
