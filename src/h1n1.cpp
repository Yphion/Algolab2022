#include <iostream>
#include <vector>

#include <map>
#include <queue>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::All_faces_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;



struct Op {
  long val;
  Face_handle f;
Op(long vx, Face_handle fx) : val(vx), f(fx) {}
};

bool operator < (const Op& e1, const Op& e2) {
return (e1.val < e2.val);
}

typedef std::priority_queue<Op> Op_heap;

void solve(int n){
  
  std::vector<K::Point_2> pts;
  pts.reserve(n);
  
  for(int i=0; i<n; ++i){
    int x, y;
    std::cin >> x >> y;
    pts.emplace_back(K::Point_2(x, y));
  }
  
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  std::map<Face_handle, int> nodes;
  
  std::vector<Face_handle> infinites;
  
  int index = 0;
  for (Face_iterator f = t.all_faces_begin(); f != t.all_faces_end(); ++f){
    if(t.is_infinite(f)){
      infinites.push_back(f);
    } 
    nodes[f] = index++;
  }
 
  long maxd = 1L << 60;
  std::vector<long> val(nodes.size(), 0L);
  Op_heap h;
  for(auto f : infinites){
    h.push(Op(maxd, f));
  }
  
  while(h.size() > 0){
    Op op = h.top();
    h.pop();
    Face_handle f = op.f;
    long v = op.val;
    int node = nodes[f];
    if (v > val[node]){
      val[node]=v;
      
      for(int i=0; i<3; ++i){
        Face_handle fnext = f->neighbor(i);
        if (t.is_infinite(fnext)){
          continue;
        }
        long width = t.segment(f, i).squared_length();
        if (v < width){
          width = v;
        }
        h.push(Op(width, fnext));
      }
    }
  }
  int m;
  std::cin >> m;
  
  for(int i=0; i<m; ++i){
    int x, y;
    long d;
    std::cin >> x >> y >> d;
    
    K::Point_2 p = K::Point_2(x,y);
    
    Face_handle f = t.inexact_locate(p);
    long vdist = CGAL::squared_distance(t.nearest_vertex(p, f)->point(), p);
    if(vdist < d || val[nodes[f]] < 4*d){
      std::cout << "n";
    } else {
      std::cout << "y";
    }
  }
  std::cout << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int n;
  std::cin >> n;
  while(n != 0){
    solve(n);
    std::cin >> n;
  }
  return 0;
}
