#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

typedef  boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
  boost::property<boost::edge_capacity_t, long,
    boost::property<boost::edge_residual_capacity_t, long,
      boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >  graph;

typedef  boost::graph_traits<graph>::edge_descriptor      edge_desc;
typedef  boost::graph_traits<graph>::out_edge_iterator      out_edge_it;

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void solve(){
  
  int n;
  std::cin >> n;
  
  graph G(n*n+2);
  edge_adder adder(G);  
  
  std::vector<std::vector<int>> M(n, std::vector<int>(n, 0));
  
  for (int i=0; i<n; ++i){
    for (int j=0; j<n; ++j){
      std::cin >> M[i][j];
    }
  }
  
  int source = n*n;
  int target = source + 1;
  
  int holes = 0;
  
  for(int i=0; i<n; ++i){
    for(int j=0; j<n; ++j){
      if(M[i][j]==0){
        holes++;
        continue;
      }
      
      int pos = i*n + j;
      if(i%2 == j%2){
        adder.add_edge(source, pos, 1);
      } else {
        adder.add_edge(pos, target, 1);
        continue;
      }
      int ii; int jj;
      if((ii=i-2) >= 0){
        if((jj=j-1) >= 0){
          if(M[ii][jj] == 1){
            adder.add_edge(pos, ii*n + jj, 1);
          }
        }
        if((jj=j+1) < n){
          if(M[ii][jj] == 1){
            adder.add_edge(pos, ii*n + jj, 1);
          }
        }
      }
      if((ii=i-1) >= 0){
        if((jj=j-2) >= 0){
          if(M[ii][jj] == 1){
            adder.add_edge(pos, ii*n + jj, 1);
          }
        }
        if((jj=j+2) < n){
          if(M[ii][jj] == 1){
            adder.add_edge(pos, ii*n + jj, 1);
          }
        }
      }
      if((ii=i+2) < n){
        if((jj=j-1) >= 0){
          if(M[ii][jj] == 1){
            adder.add_edge(pos, ii*n + jj, 1);
          }
        }
        if((jj=j+1) < n){
          if(M[ii][jj] == 1){
            adder.add_edge(pos, ii*n + jj, 1);
          }
        }
      }
      if((ii=i+1) < n){
        if((jj=j-2) >= 0){
          if(M[ii][jj] == 1){
            adder.add_edge(pos, ii*n + jj, 1);
          }
        }
        if((jj=j+2) < n){
          if(M[ii][jj] == 1){
            adder.add_edge(pos, ii*n + jj, 1);
          }
        }
      }
    }
  }
  
        
  int flow = boost::push_relabel_max_flow(G, source, target);
  std::cout << (n*n-flow-holes) << std::endl;
}

int main() {
  int t;
  std::cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
