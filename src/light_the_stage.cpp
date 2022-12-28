#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Triangulation_vertex_base_with_info_2<int,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Vertex_handle Vertex_handle;


void solve(){
  int m, n;
  std::cin >> m >> n;
  
  std::vector<K::Point_2> points;
  std::vector<int> radii;
  
  points.reserve(m);
  radii.reserve(m);
  
  for(int i=0; i<m; ++i){
    int x, y, r;
    std::cin >> x >> y >> r;
    points.emplace_back(K::Point_2(x,y));
    radii.push_back(r);
  }
  
  int h;
  std::cin >> h;
  
  std::vector<std::pair<K::Point_2,int>> lights;
  lights.reserve(n);
  
  for(int i=0; i<n; ++i){
    int x, y;
    std::cin >> x >> y;
    lights.emplace_back(K::Point_2(x,y), i);
  }
  
  Triangulation t;
  t.insert(lights.begin(), lights.end());
  
  std::vector<std::vector<int>> col(n, std::vector<int>(0));
  
  bool done = false;
  
  for(int i=0; i<m; ++i){
    K::Point_2 p1 = points[i];
    Vertex_handle p2 = t.nearest_vertex(p1);
    if (CGAL::squared_distance(p1, p2->point()) < ((long)h+(long)radii[i])*((long)h+(long)radii[i])){
      col[p2->info()].push_back(i);
    } else {
      done = true;
      std::cout << i << " ";
    }
  }
  
  if (done){
    std::cout << std::endl;
    return;
  } 
  
  std::vector<int> res;
  
  for(int i=n-1; i>0; i--){
    Vertex_handle p = t.nearest_vertex(lights[i].first);
    t.remove(p);
    
    for(int x : col[i]){
      K::Point_2 p1 = points[x];
      Vertex_handle p2 = t.nearest_vertex(p1);
      if (CGAL::squared_distance(p1, p2->point()) < ((long)h+(long)radii[x])*((long)h+(long)radii[x])){
        col[p2->info()].push_back(x);
      } else {
        done = true;
        res.push_back(x);
      }
    }
    
    if (done){
      sort(res.begin(), res.end());
      for (auto x : res){
        std::cout << x << " ";
      }
      std::cout << std::endl;
      return;
    }
  }
  
  for (int i=0; i<m; ++i){
    std::cout << i << " ";
  }
  std::cout << std::endl;
  
}

int main(){
  int t;
  std::cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
