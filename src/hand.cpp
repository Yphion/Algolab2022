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
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

void solve(){
  int n, k; Index f0; long s0;
  std::cin >> n >> k >> f0 >> s0;
  
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> points;
  
  for(int i=0; i<n; ++i){
    int x,y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  
  Delaunay t;
  t.insert(points.begin(), points.end());
  
  EdgeV edges;
  edges.reserve(3*n);
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });

  Index n_components = n;
  
  int overk = n/k;
  
  std::vector<int> dist = {n, 0, 0, 0};
  
  std::vector<int> rep(n, 0);
  for(int i=1; i<n; ++i){
    rep[i] = i;
  }
  
  std::vector<int> setsize(n, 1);
  std::vector<std::vector<int>> sets(n, std::vector<int>(1,0));
  for(int i=1; i<n; ++i){
    sets[i][0] = i;
  }
  
  
  long s = 0;
  int f = overk;
  
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    
    Index c1 = rep[std::get<0>(*e)];
    Index c2 = rep[std::get<1>(*e)];
    if (c1 != c2) {
      
      if(overk == (int)f0){
          s = std::get<2>(*e);
      }
      
      --n_components;

      if(setsize[c1] < setsize[c2]){
        std::swap(c1,c2);
      }
      
      int q1 = std::min(setsize[c1]-1, 3);
      int q2 = std::min(setsize[c2]-1, 3);
      
      dist[q1]--;
      dist[q2]--;
      
      setsize[c1] += setsize[c2];
      q1 = std::min(setsize[c1]-1, 3);
      dist[q1]++;

      if (k==4){
        overk = dist[3];
        int ones = dist[0];
        int twos = dist[1];
        if(dist[2] <= ones){
          overk += dist[2];
          ones -= dist[2];
        } else {
          twos += dist[2]-ones;
          overk += ones;
          ones = 0;
        }
        overk += twos/2;
        if(twos%2 != 0 && ones > 1){
            overk++;
            ones -= 2;
        }
        overk += ones/4;
        
      } else if (k==3) {
        overk = dist[3] + dist[2];
        if(dist[1] <= dist[0]){
          overk += dist[1] + (dist[0]-dist[1])/3;
        } else {
          overk += dist[0] + (dist[1]-dist[0])/2;
        }
        
      } else if (k==2) {
        overk = dist[0]/2 + dist[1]+dist[2]+dist[3];
        
      } else if (k==1){
        overk = dist[0]+dist[1]+dist[2]+dist[3];
      }
      
      for(int x : sets[c2]){
        rep[x] = c1;
        sets[c1].push_back(x);
      }
    }
    
    if (std::get<2>(*e) < s0){
      f = overk;
    }
    
    if (n_components == 1) break;
  }
  
  std::cout << s << " " << f << std::endl;
  
}

int main(){
  int t;
  std::cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
