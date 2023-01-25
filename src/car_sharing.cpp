#include <iostream>
#include <vector>
#include <set>
#include <tuple>

#include <boost/graph/adjacency_list.hpp>
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

typedef std::tuple<int,int,int,int,int> Req; 

void solve(){
  int n, s;
  std::cin >> n >> s;
  
  std::vector<int> S;
  int lsum = 0;
  for(int i=0; i<s; ++i){
    int l;
    std::cin >> l;
    lsum += l;
    S.push_back(l);
  }
  
  std::vector<std::set<Req>> Starts(s, std::set<Req>());
  
  int index = 0;
  
  for(int i=0; i<n; ++i){
    int si, ti, di, ai, pi;
    std::cin >> si >> ti >> di >> ai >> pi;
    Starts[si-1].insert(Req(di,ai,ti-1,pi,index++));
  }
  
  graph G(s+n+2);
  edge_adder adder(G);  
  
  const int source = s + n;
  const int sink = source + 1;
  const int offset = n;
  const long maxt = 100000L;
  
  int pretime;
  int prenode;
  
  for(int i=0; i<s; ++i){
    adder.add_edge(source, offset+i, S[i], 0);
    pretime = 0;
    prenode = offset+i;
    
    for(Req r : Starts[i]){
      int dep = std::get<0>(r);
      int arr = std::get<1>(r);
      int tgt = std::get<2>(r);
      int prf = std::get<3>(r);
      int ind = std::get<4>(r);
      
      adder.add_edge(prenode, ind, lsum, 100*(dep-pretime));
      
      prenode = ind;
      pretime = dep;
      
      auto rt = Starts[tgt].lower_bound(Req(arr, 0, 0, 0, 0));
      if(rt == Starts[tgt].end()){
        adder.add_edge(ind, sink, 1, 100L*(maxt-dep) - prf);
      } else {
        adder.add_edge(ind, std::get<4>(*rt), 1, 100L*(std::get<0>(*rt)-dep) - prf);
      }
    }
    
    adder.add_edge(prenode, sink, lsum, 100L*(maxt-pretime));
  }
    
  boost::successive_shortest_path_nonnegative_weights(G, source, sink);
  long cost = boost::find_flow_cost(G);
  
  std::cout << (lsum*100L*maxt-cost) << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  while(t--) solve();
  return 0;
}
