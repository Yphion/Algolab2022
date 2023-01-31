#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef int                                                    Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

std::ostream& operator<<(std::ostream& o, const Edge& e) {
  return o << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e);
}


void solve(){
  int n, m, k;
  long s;
  std::cin >> n >> m >> s >> k;
  
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  for (Index i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  
  Delaunay t;
  t.insert(points.begin(), points.end());

  EdgeV edges;
  edges.reserve(3*n+m);
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }


  for(int i=0; i<m; ++i){
    int x, y;
    std::cin >> x >> y;
    K::Point_2 p(x,y);
    auto nv = t.nearest_vertex(p);
    edges.emplace_back(-1, nv->info(), 4*CGAL::squared_distance(p, nv->point()));
  }
  
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });
  
  std::vector<int> rep;
  rep.reserve(n);
  
  std::vector<std::vector<int>> friends(n);
  for(int i=0; i<n; ++i){
    rep.push_back(i);
    friends[i].push_back(i);
  }
  
  std::vector<int> bones(n, 0);
  
  long a = -1;
  long b = -1;
  
  for (Edge &e : edges) {
    int u = std::get<0>(e);
    int v = std::get<1>(e);
    K::FT d = std::get<2>(e);
    
    if(a==-1 && d > s) {
      for(int i=0; i<n; ++i){
        if(bones[i]>a){
          a = bones[i];
        }
      }
      if(b != -1){
        break;
      }
    }
    
    if(u == -1){
      bones[rep[v]]++;
      if(b == -1 && bones[rep[v]] >= k){
        b = ceil(d);
        
        if(a != -1){
          break;
        }
      }
    } else {
      
      int i1 = rep[u];
      int i2 = rep[v];
      if(i1 != i2){
        if(friends[i1].size() > friends[i2].size()){
          std::swap(i1, i2); 
        }
        
        for(int f : friends[i1]){
          rep[f] = i2;
          friends[i2].push_back(f);
        }
        
        bones[i2] += bones[i1];
        if(b==-1 && bones[i2] >= k){
          b = ceil(d);
        
          if(a != -1){
            break;
          }
        }
      }
    }
  }
  
  if(a==-1){
    for(int i=0; i<n; ++i){
      if(bones[i] > a){
        a = bones[i];
      }
    }
  }
  
  std::cout << a << " " << b << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; 
  std::cin >> t;
  while(t--) solve();
  return 0;
}
