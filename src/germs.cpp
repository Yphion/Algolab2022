#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

int dist_to_time(long x){
  long y = sqrt((sqrt(x)-1)/2);
  while((2*y*y+1)*(2*y*y+1) < x){
    y++;
  }
  return y;
}

void solve(int n){
  int l, b, r, t;
  std::cin >> l >> b >> r >> t;
  
  std::vector<std::pair<int,int>> coords;
  coords.reserve(n);
  
  std::vector<std::pair<K::Point_2,int>> points;
  points.reserve(n);
  
  for(int i=0; i<n; ++i){
    int x, y;
    std::cin >> x >> y;
    coords.push_back(std::pair<int,int>(x,y));
    points.emplace_back(K::Point_2(x, y), i);
  }
  
  Delaunay q;
  q.insert(points.begin(), points.end());
  
  std::vector<long> opt;
  opt.reserve(n);
  
  for(int i=0; i<n; ++i){
    std::pair<int,int> p1 = coords[i];
    
    long mindist = (long)(p1.first-l)*(long)(p1.first-l);
    long alt = (long)(p1.first-r)*(long)(p1.first-r);
    if (alt < mindist){
      mindist = alt;
    }
    alt = (long)(p1.second-t)*(long)(p1.second-t);
    if (alt < mindist){
      mindist = alt;
    }
    alt = (long)(p1.second-b)*(long)(p1.second-b);
    if (alt < mindist){
      mindist = alt;
    }
    opt.push_back(4*mindist);
  }
  

  for (auto e = q.finite_edges_begin(); e != q.finite_edges_end(); ++e) {
    int i1 = e->first->vertex((e->second+1)%3)->info();
    int i2 = e->first->vertex((e->second+2)%3)->info();
    
    std::pair<int,int> p1 = coords[i1];
    std::pair<int,int> p2 = coords[i2];
    
    long xd = (p1.first-p2.first);
    long yd = (p1.second-p2.second);
    long dist = xd*xd+yd*yd;
    if(dist < opt[i1]){
      opt[i1] = dist;
    }
    if(dist < opt[i2]){
      opt[i2] = dist;
    }
  }
  
  std::sort(opt.begin(), opt.end());
  
  long first = opt[0];
  long mid = opt[n/2];
  long last = opt[n-1];
  
  std::cout << dist_to_time(first) << " " << dist_to_time(mid) << " " << dist_to_time(last) << std::endl;
}

int main(){
  int n;
  std::cin >> n;
  while(n != 0){
    solve(n);
    std::cin >> n;
  }
  return 0;
}
