#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef int                                                   Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef Delaunay::Face_handle Face_handle;
typedef std::pair<K::FT, K::FT> DPair;

void solve(){
  int n, h;
  long s;
  std::cin >> n >> s >> h;
  
  K::FT ss = K::FT(s);
  
  long count2 = 0;
  long count3 = 0;
  long counts = 0;
  long countmax = 1;
  
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
  
  K::FT opt = K::FT(1L<<60);
  
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    K::FT dist = t.segment(e).squared_length();
    if(dist < opt){
      opt = dist;
      count2 = 1;
    } else if(dist == opt){
      count2++;
    }
  }
  
  std::map<Face_handle, std::pair<K::Point_2,K::FT>> fmap;
  opt = K::FT(1L<<60);
  
  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f) {
    K::Point_2 p = t.dual(f);
    K::Point_2 pt = t.nearest_vertex(p, f)->point();
    K::FT dist = CGAL::squared_distance(p, pt);
    if(dist < opt){
      opt = dist;
      count3 = 1;
    } else if(dist == opt){
      count3++;
    }
    
    fmap[f]=std::pair<K::Point_2, K::FT>(p, dist);
  }
  
  std::vector<DPair> D;
  K::FT inf(1L<<62);
  
  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f) {
    std::pair<K::Point_2, K::FT> p = fmap[f];
    for(int i=0; i<3; ++i){
      Face_handle fn = f->neighbor(i);
      if(!t.is_infinite(fn) && fn < f){
        continue;
      }
      
      auto pt1x = f->vertex((i+1) % 3);
      auto pt2x = f->vertex((i+2) % 3);
      
      K::Point_2 pt1 = pt1x->point();
      K::Point_2 pt2 = pt2x->point();
      
      int pt1id = pt1x->info();
      int pt2id = pt2x->info();
      
      K::Point_2 mid = CGAL::midpoint(pt1, pt2);
      auto pmx = t.nearest_vertex(mid, f);
      if(t.is_infinite(fn)){
        if(pmx->info() == pt1id || pmx->info() == pt2id){
          
          K::FT dist = CGAL::squared_distance(pmx->point(), mid);
          if(dist <= ss){
            counts++;
          }
          
          D.push_back(DPair(dist, inf));
        } else {
          
          K::FT dist = p.second;
          if(dist <= ss){
            counts++;
          }
          D.push_back(DPair(dist, inf));
        }
        
      } else {
        std::pair<K::Point_2, K::FT> pn = fmap[fn];
        if(pmx->info() == pt1id || pmx->info() == pt2id){
          
          K::FT dist = CGAL::squared_distance(pmx->point(), mid);
          if(dist <= ss && (ss <= p.second || ss <= pn.second)){
            counts++;
          }
          
          if(p.second < pn.second){
            D.push_back(DPair(dist, pn.second));
          } else {
            D.push_back(DPair(dist, p.second));
          }
          
        } else {
          
          if((p.second <= ss && ss <= pn.second) || (pn.second <= ss && ss <= p.second) ){
            counts++;
          }
          
          if(p.second < pn.second){
            D.push_back(DPair(p.second, pn.second));
          } else {
            D.push_back(DPair(pn.second, p.second));
          }
          
        }
        
      }
    }
  }
  
  std::sort(D.begin(), D.end());
  
  int low = 1;
  int count = 1;
  std::multiset<K::FT> highset;
  highset.insert(D[0].second);
  
  while(low < D.size()){
    K::FT lowval = D[low].first;

    highset.erase(highset.begin(), highset.lower_bound(lowval));
    highset.insert(D[low].second);
    count = highset.size();
    
    if(count > countmax){
      countmax = count;
    }
    low++;
  }
  
  std::cout << count2 << " " << count3 << " " << counts << " " << countmax << std::endl;
}

int main(){
  int t;
  std::cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
