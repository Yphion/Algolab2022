#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>

// Delauney Triangulation

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;

// Linear Programming

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

// Helpers

typedef std::pair<K::Point_2, long> Circle;
typedef std::tuple<K::Point_2, long, long> House;


double floor_to_double(const CGAL::Quotient<ET>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void solve(){
  int n, m, c;
  std::cin >> n >> m >> c;

  std::vector<K::Point_2> pts;
  pts.reserve(n+m);
  
  // Warehouses
  
  std::vector<House> W;
  W.reserve(n);
  
  for(int i=0; i<n; ++i){ 
    long x, y, s, a;
    std::cin >> x >> y >> s >> a;
    K::Point_2 p(x,y);
    pts.push_back(p);
    W.push_back(House(p, s, a));
  }
  
  // Statiums
  
  std::vector<House> S;
  S.reserve(m);
  
  for(int i=0; i<m; ++i){ 
    long x, y, d, u;
    std::cin >> x >> y >> d >> u;
    K::Point_2 p(x,y);
    pts.push_back(p);
    S.push_back(House(p, d, u));
  }
  
  // Estimated Rewards
  
  std::vector<std::vector<long>> R(n, std::vector<long>(m, 0));
  
  for(int i=0; i<n; ++i){ 
    for(int j=0; j<m; ++j){
      long r;
      std::cin >> r;
      
      R[i][j] = 100*r;
    }
  }
  
  // Triangulation to find closest house to circle
  
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  // Contour lines
  
  std::vector<Circle> C;
  C.reserve(100);
  
  for(int i=0; i<c; ++i){ 
    int x, y;
    long r;
    std::cin >> x >> y >> r;
    r *= r;
    K::Point_2 p(x,y);
    if(CGAL::squared_distance(p, t.nearest_vertex(p)->point()) <= r){
      C.push_back(Circle(p, r));
    }
  }
  
  // Build datastructures for contour line traversal lookup
  
  std::sort(C.begin(), C.end(),
      [](const Circle& e1, const Circle& e2) -> bool {
        return e1.second > e2.second;
            });
  
  std::vector<std::vector<int>> WC(n, std::vector<int>()); 
  
  for(int i=0; i<n; ++i){
    for(int j=0; j<C.size(); ++j){
      Circle cir = C[j];
      
      if (CGAL::squared_distance(cir.first, std::get<0>(W[i])) <= cir.second){
        WC[i].push_back(j);
      }
    }
  }

  std::vector<std::vector<int>> SC(m, std::vector<int>()); 
  
  for(int i=0; i<m; ++i){
    for(int j=0; j<C.size(); ++j){
      Circle cir = C[j];
      
      if (CGAL::squared_distance(cir.first, std::get<0>(S[i])) <= cir.second){
        SC[i].push_back(j);
      }
    }
  }
  
  // Reward compution
  
  for(int i=0; i<n; ++i){
    for(int j=0; j<m; ++j){
      int k = 0;
      while( k < WC[i].size() && k < SC[j].size()){
        if(WC[i][k] == SC[j][k]){
          k++;
        } else {
          break;
        }
      }
      
      int t = WC[i].size() + SC[j].size() - 2*k;
      R[i][j] -= t;
    }
  }
  
  // Construct Linear Program
  
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  
  int index = 0;
  
  for(int i=0; i<m; ++i){ // sum_w of a_w,s <= d_s
    for(int j=0; j<n; ++j){
      lp.set_a(m*j+i, index,  1);
    }
    lp.set_b(index, std::get<1>(S[i]));
    index++;
  }
  
  for(int i=0; i<m; ++i){ // sum_w of a_w,s >= d_s
    for(int j=0; j<n; ++j){
      lp.set_a(m*j+i, index,  -1);
    }
    lp.set_b(index, -std::get<1>(S[i]));
    index++;
  }
  
  for(int i=0; i<m; ++i){ // sum_w of a_w,s <= u_s
    for(int j=0; j<n; ++j){
      lp.set_a(m*j+i, index, std::get<2>(W[j]));
    }
    lp.set_b(index, 100L*std::get<2>(S[i]));
    index++;
  }

  for(int i=0; i<n; ++i){ // sum_s of a_w,s <= s_w
    for(int j=0; j<m; ++j){
      lp.set_a(m*i+j, index,  1);
    }
    lp.set_b(index, std::get<1>(W[i]));
    index++;
  }
  
  for(int i=0; i<n; ++i){ // max sum_s,w a_s,w r_s,w
    for(int j=0; j<m; ++j){
      lp.set_c(m*i+j, -R[i][j]);
    }
  }
  
  // Solve Linear Program
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  
  if (s.is_infeasible()) { 
    std::cout << "RIOT!" << std::endl;
    return;
  }
  
  std::cout << (long)floor_to_double(-s.objective_value()/100) << std::endl;
}


int main(){
  int t;
  std::cout << std::fixed;
  std::cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}


