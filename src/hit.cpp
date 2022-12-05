#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <vector>
#include <CGAL/Segment_2.h>
#include <CGAL/Ray_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel   EK;

void solve(int n){
  
  long x, y, a, b;
  long r, s, t, u;
  std::cin >> x >> y >> a >> b;
  
  EK::Ray_2 q(EK::Point_2(x,y), EK::Point_2(a,b));
  
  bool res = false;
  
  for (int i=0; i<n; ++i){
    
    std::cin >> r >> s >> t >> u;
    
    if (res){
      continue;
    }
    
    EK::Segment_2 z(EK::Point_2(r,s), EK::Point_2(t,u));
    if (CGAL::do_intersect(z, q)){
      res = true;
    }
  }
  
  std::cout << (res ? "yes" : "no") << std::endl;
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int n;
  std::cin >> n;
  
  while(n!=0){
    solve(n);
    std::cin >> n;
  }
  
  return 0;
}
