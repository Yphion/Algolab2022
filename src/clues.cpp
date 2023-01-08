#include <iostream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/bipartite.hpp>


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS   
    >          graph;
typedef boost::graph_traits<graph>::vertex_descriptor    vertex_desc;  
typedef boost::graph_traits<graph>::edge_iterator    edge_it;  
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef Delaunay::Vertex_handle Vertex_handle;

void solve(){
  int n, m; long r;
  std::cin >> n >> m >> r;
  
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  
  for(int i=0; i<n; ++i){
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  
  Delaunay t;
  t.insert(points.begin(), points.end());
  
  graph G(n);
  std::vector<std::vector<int>> Adj(n, std::vector<int>(0,0));
  
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    if (t.segment(e).squared_length() > r*r){
      continue;
    }
    
    boost::add_edge(i1, i2, G);
    Adj[i1].push_back(i2);
    Adj[i2].push_back(i1);
  }
  
  bool bipartite = is_bipartite (G);
  
  for(int i=0; i<n; ++i){
    K::Point_2 x = points[i].first;
    
    for (int j : Adj[i]){
      for (int k : Adj[j]){
        if (k==i) continue;
        K::Point_2 y = points[k].first;
        if(CGAL::squared_distance(x,y) <= r*r){
          bipartite = false;
        }
      }
    }
  }
  
  std::vector<int> component_map(n);
  int ncc = boost::connected_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G))); 
  
  for(int i=0; i<m; ++i){
    int xa, ya, xb, yb;
    std::cin >> xa >> ya >> xb >> yb;
    K::Point_2 a(xa,ya);
    K::Point_2 b(xb,yb);
    
    Vertex_handle at = t.nearest_vertex(a);
    Vertex_handle bt = t.nearest_vertex(b);
    bool connected = CGAL::squared_distance(a,b)<=r*r || ( CGAL::squared_distance(a,at->point())<=r*r && CGAL::squared_distance(b,bt->point())<=r*r && component_map[at->info()] == component_map[bt->info()]);
    if(bipartite&&connected){
      std::cout << "y";
    } else {
      std::cout << "n";
    }
  }
  std::cout<<std::endl;
}

int main(){
  
  int t;
  std::cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
