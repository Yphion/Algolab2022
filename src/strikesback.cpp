#include <iostream>
#include <vector>

// Delauney Triangulation

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef int                                                    Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

// Linear Program

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Gmpq.h>

typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void solve(){
  bool res = false;
  
  int a, s, b, e;
  std::cin >> a >> s >> b >> e;
  
  // Asteroid Particles
  
  std::vector<std::pair<long, long>> A;
  A.reserve(a);
  
  std::vector<int> Ad;
  Ad.reserve(a);
  
  for(int i=0; i<a; ++i){
    int x, y, d;
    std::cin >> x >> y >> d;
    A.push_back(std::pair<long,long>(x,y));
    Ad.push_back(d);
  } 
  
  // Shooting Targets
  
  std::vector<std::pair<long, long>> S;
  S.reserve(s);
  
  std::vector<K::Point_2> Sc;
  Sc.reserve(s);
  
  for(int i=0; i<s; ++i){
    long x, y;
    std::cin >> x >> y;
    S.push_back(std::pair<long, long>(x,y));
    Sc.push_back(K::Point_2(x,y));
  }
  
  // Bounty Hunters
  
  std::vector<std::pair<K::Point_2,Index>> Bc;
  Bc.reserve(b);
  
  std::vector<std::pair<long, long>> B;
  B.reserve(b);
  
  for(int i=0; i<b; ++i){
    int x, y;
    std::cin >> x >> y;
    Bc.emplace_back(K::Point_2(x, y), i);
    B.push_back(std::pair<long,long>(x,y));
  }
  
  Delaunay t;
  t.insert(Bc.begin(), Bc.end());
  
  // Find effects
  
  std::vector<std::vector<IT>> E(s, std::vector<IT>(a, IT(0,1)));
  
  for(int i=0; i<s; ++i){
    
    bool safe = true;
    long r = 0;
    if(b > 0){
      safe = false;
      int rind = t.nearest_vertex(Sc[i])->info();
      long dx = (S[i].first-B[rind].first);
      long dy = (S[i].second-B[rind].second);
      r = dx*dx + dy*dy;
    }
    
    for(int j=0; j<a; ++j){
      long dx = (S[i].first-A[j].first);
      long dy = (S[i].second-A[j].second);
      long dist = dx*dx+dy*dy;
      if(safe || dist < r){
        if(dist == 0L){
          dist = 1L;
        }
        E[i][j] = IT(1, dist);
      }
    }
    
  }
  
  // Construct Linear Program
  
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  int index = 0;
  
  for(int i=0; i<s; ++i){ // sum_s e_s <= e
    lp.set_a(i, index,  1);
  }
  lp.set_b(index, e);
  index++;
  
  for (int i=0; i<a; ++i){ // sum_s e_s damage_s,a >= d_a
    for(int j=0; j<s; ++j){
      lp.set_a(j, index, -E[j][i]);
    }
    lp.set_b(index, -Ad[i]);
    index++;
  }
  
  // Solve Linear Program
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  res = !sol.is_infeasible();
  
  std::cout << (res ? "y" : "n") << std::endl;
}

int main(){
  int t;
  std::cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  return 0;
}
