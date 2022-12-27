#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Vertex_handle Vertex_handle;

void solve(int n){
  
  std::vector<K::Point_2> points;
  points.reserve(n);
  
  for (int i=0; i<n; ++i){
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y));
    
  }
  
  Triangulation t;
  t.insert(points.begin(), points.end());
  
  int m; 
  std::cin >> m;
  
  for (int i=0; i<m; ++i){
    int x, y;
    std::cin >> x >> y;
    K::Point_2 p1 = K::Point_2(x,y);
    Vertex_handle p2 = t.nearest_vertex(p1);
    std::cout << std::setprecision(0) <<std::fixed <<CGAL::squared_distance(p1, p2->point()) << std::endl;
  }
}

int main(){
  int n;
  std::cin >> n;
  while(n != 0){
    solve(n);
    std::cin >> n;
  }
}
