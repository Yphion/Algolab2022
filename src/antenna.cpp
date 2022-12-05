#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/number_utils.h>
#include <vector>

typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;

long ceil_to_long(const K::FT& x)
{
  long a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void solve(int n){
  
  long xin, yin;
  
  std::vector<K::Point_2> P;
  P.reserve(n);
  for(int i=0; i<n; ++i){
    std::cin >> xin >> yin;
    P.push_back(K::Point_2(xin, yin));
  }
  
  Min_circle mc(P.begin(), P.end(), true);
  Traits::Circle c = mc.circle();
  
  if (c.is_degenerate()){
    std::cout << 0 << std::endl;
    return;
  }
  
  K::FT sr = c.squared_radius();
  std::cout << ceil_to_long(CGAL::sqrt(sr)) << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int n;
  std::cin >> n;
  while(n){
    solve(n);
    std::cin >> n;
  }
  
  return 0;
}
