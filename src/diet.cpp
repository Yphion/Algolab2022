#include <iostream>
#include <vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;



void solve(int n, int m){
  
  std::vector<int> mn;
  std::vector<int> mx;
  mn.reserve(n);
  mx.reserve(n);
  
  for(int i=0; i<n; ++i){
    int mni, mxi;
    std::cin >> mni >> mxi;
    mn.push_back(mni);
    mx.push_back(mxi);
  }

  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  
  std::vector<std::vector<int>> C(m, std::vector<int>(n, 0));
  
  std::vector<int> p;
  p.reserve(m);
  
  for(int i=0; i<m; ++i){
    int tmp;
    std::cin >> tmp;
    p.push_back(tmp);
    
    for(int j=0; j<n; ++j){
      std::cin >> tmp;
      C[i][j] = tmp;
    }
  }
  
  for(int i=0; i<n; ++i){
    lp.set_b(i, -mn[i]);
    lp.set_b(n+i, mx[i]);
    for(int j=0; j<m; ++j){
      lp.set_a(j, i, -C[j][i]);
      lp.set_a(j, n+i, C[j][i]);
    }
  }
  
  for(int j=0; j<m; ++j){
    lp.set_c(j, p[j]);
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  
  if (s.is_unbounded()){
    std::cout << "unbounded" << std::endl;
    return;
  }
  
  if (s.is_infeasible()) { 
    std::cout << "No such diet." << std::endl;
    return;
  }
  
  std::cout << floor(CGAL::to_double(s.objective_value())) << std::endl;
}


int main(){
  
  int n, m;
  std::cin >> n >> m;
  while(n > 0){
    solve(n, m);
    std::cin >> n >> m;
  }
  
  return 0;
  
}
