#include <iostream>
#include <vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;



void solve(int n){
  
  int d;
  std::cin >> d;
  
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  
  std::vector<int> Ssq;
  std::vector<std::vector<int>> A(n, std::vector<int>(d+1, 0));
  Ssq.reserve(n);
  
  for(int i=0; i<n; ++i){
    int tmp;
    int ssq = 0;
    for(int j=0; j<d; j++){
      std::cin >> tmp;
      A[i][j] = tmp;
      lp.set_a(j, i, tmp);
      ssq += tmp*tmp;
    }
    Ssq.push_back(sqrt(ssq));
    
    std::cin >> tmp;
    A[i][d] = tmp;
    lp.set_b(i, tmp);
  }
  
  for(int i=0; i<n; ++i){
    for(int j=0; j<d; ++j){
      lp.set_a(j, n+i, A[i][j]);
    }
    lp.set_a(d, n+i, Ssq[i]);
    lp.set_b(n+i, A[i][d]);
  }
  
  lp.set_a(d, 2*n, -1);
  lp.set_b(2*n, 0);

  lp.set_c(d, -1);
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  
  if (s.is_unbounded()){
    std::cout << "inf" << std::endl;
    return;
  }
  
  if (s.is_infeasible()) { 
    std::cout << "none" << std::endl;
    return;
  }
  
  std::cout << abs(floor(-CGAL::to_double(s.objective_value()))) << std::endl;

}


int main(){
  
  int n;
  std::cin >> n;
  while(n > 0){
    solve(n);
    std::cin >> n;
  }
  
  return 0;
  
}
