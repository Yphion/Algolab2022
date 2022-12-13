#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void solve(int p){
  
  int a, b;
  std::cin >> a >> b;
  
  Program lp (CGAL::SMALLER, p==1, 0, p==2, 0); 

  const int X = 0; 
  const int Y = 1;
  const int Z = 2;
  
  if (p == 1){
    lp.set_a(X, 0,  1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);
    lp.set_a(X, 1,  4); lp.set_a(Y, 1, 2); lp.set_b(1, a*b);
    lp.set_a(X, 2,  -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);
    
    lp.set_c(X, a); lp.set_c(Y, -b); lp.set_c0(0);
  } else {
    lp.set_a(X, 0,  -1); lp.set_a(Y, 0, -1); lp.set_b(0, 4);
    lp.set_a(X, 1,  -4); lp.set_a(Y, 1, -2); lp.set_a(Z, 1, -1); lp.set_b(1, a*b);
    lp.set_a(X, 2,  1); lp.set_a(Y, 2, -1); lp.set_b(2, 1);
    
    lp.set_c(X, a); lp.set_c(Y, b); lp.set_c(Z, 1);
  }

  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  
  if (s.is_unbounded()){
    std::cout << "unbounded" << std::endl;
    return;
  }
  
  if (s.is_infeasible()) { 
    std::cout << "no" << std::endl;
    return;
  }
  
  if (p==1) {
    std::cout << floor(-CGAL::to_double(s.objective_value())) << std::endl;
  } else {
    std::cout << ceil(CGAL::to_double(s.objective_value())) << std::endl;
  }
   
}

int main(){
  
  int p;
  std::cin >> p;
  while(p > 0){
    solve(p);
    std::cin >> p;
  }
  
  return 0;
}
