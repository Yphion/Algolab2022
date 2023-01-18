#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <tuple>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS  
    >          graph;
typedef boost::graph_traits<graph>::vertex_descriptor    vertex_desc;  
typedef boost::graph_traits<graph>::edge_iterator    edge_it;  

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef int                                          Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;


typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

void solve(){
  int n;
  long r;
  std::cin >> n >> r;
  
  r = r*r;
  
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  
  int low = 1;
  int high = n/2+1;
  
  while(high > low+1){
    
    int k = (high+low)/2;
    
    Delaunay t;
    t.insert(points.begin()+k, points.end());
    
    graph G(n-k);
    
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
      Index i1 = e->first->vertex((e->second+1)%3)->info();
      Index i2 = e->first->vertex((e->second+2)%3)->info();
      
      if (t.segment(e).squared_length() <= r){
        boost::add_edge(i1-k, i2-k, G);
      }
    }
    
    std::vector<int> component_map(n-k);
    int ncc = boost::connected_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G))); 
    std::vector<int> components(ncc, 0);
    for(int i=0; i<n-k; ++i){
      components[component_map[i]]++;
    }
    
    int size = *std::max_element(std::begin(components), std::end(components));
    
    if(size >= k){
      low = k;
    } else {
      high = k;
      low = std::max(low, size);
    }
    
  }
  
  std::cout << low << std::endl;
  
}

int main(){
  int t;
  std::cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
