#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

#include <vector>
#include <CGAL/Segment_2.h>
#include <CGAL/Ray_2.h>

#include <algorithm>
#include <random>

typedef CGAL::Exact_predicates_exact_constructions_kernel   EK;

auto rng = std::default_random_engine {};

long floor_to_long(const EK::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void solve(int n){
  
  long x, y, a, b;
  long r, s, t, u;
  std::cin >> x >> y >> a >> b;
  
  EK::Point_2 source(x,y);
  EK::Point_2 target(a,b);
  EK::Ray_2 q(source, target);
  EK::Segment_2 qq;
  
  EK::FT mn = EK::FT(1L<<52)*EK::FT(1L<<52);
  EK::Point_2 pt;
  bool found = false;
  
  std::vector<EK::Segment_2*> Sx;
  
  for(int i=0; i<n; ++i){
    std::cin >> r >> s >> t >> u;
    EK::Segment_2* z = new EK::Segment_2(EK::Point_2(r,s), EK::Point_2(t,u));
    Sx.push_back(z);
  }
  
  std::shuffle(std::begin(Sx), std::end(Sx), rng);
    
  for (int i=0; i<n; ++i){

      EK::Segment_2 z = *(Sx[i]);
      
      auto isq = found ? CGAL::intersection(qq, z) : CGAL::intersection(q, z);
      
      EK::Point_2 pcand;
      if (not isq){
        continue;
      }
      
      if (const EK::Point_2* op = boost::get<EK::Point_2>(&*isq)){
        pcand = *op;
        EK::FT val = CGAL::squared_distance(pcand, source);
        if (val < mn){
          mn = val;
          pt = pcand;
          found = true;
          qq = EK::Segment_2(source, pt);
        }
        
      } else { //if  (const EK::Segment_2* op2 = boost::get<EK::Segment_2>(&*isq)) 
        pcand = z.vertex(0);
        EK::FT d1 = CGAL::squared_distance(pcand, source);
        EK::FT d2 = CGAL::squared_distance(z.vertex(1), source);
        
        if (d1 > d2){
          pcand = z.vertex(1);
          d1 = d2;
        }
        
        if (d1 < mn){
          mn = d1;
          pt = pcand;
          found = true;
          qq = EK::Segment_2(source, pt);
        }
      }
  } 
  if (found) {
    std::cout << floor_to_long(pt.x()) << " " << floor_to_long(pt.y()) << std::endl;
  } else {
    std::cout << "no" << std::endl;
  }
  
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
