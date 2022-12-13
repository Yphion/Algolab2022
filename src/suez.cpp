#include <iostream>
#include <vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(CGAL::Quotient<ET> x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return abs(-a);
}

void solve(){
  
  int n, m;
  long h, w;
  
  std::cin >> n >> m >> h >> w;
  
  std::vector<std::pair<int,int>> N;
  N.reserve(n);
  
  std::vector<std::pair<int,int>> M;
  M.reserve(m);
  
  for(int i=0; i<n; ++i){
    int x, y;
    std::cin >> x >> y;
    
    N.push_back(std::pair<int,int>(x,y));
  }
  
  for(int j=0; j<m; ++j){
    int x, y;
    std::cin >> x >> y;
    
    M.push_back(std::pair<int,int>(x,y));
  }
  
  Program lp (CGAL::SMALLER, true, 1, false, 0); 
  
  int c = 0;
  
  for(int i=0; i<n; ++i){
    
    std::vector<int> mns(4, 0);
    std::vector<bool> mnb(4, false);
    
    for(int j=0; j<m; ++j){
      
      bool tr = w*N[i].second - h*M[j].first + h*N[i].first <= w*M[j].second;
      
      bool tl = w*N[i].second + h*M[j].first - h*N[i].first <= w*M[j].second;
      
      if(tl && tr){ //top
        int val = 2*(M[j].second-N[i].second)-h;
        if (val < mns[0] || not mnb[0]){
          mnb[0] = true;
          mns[0] = val;
        }
      } else if (tl && !tr) { //left
        int val = 2*(N[i].first-M[j].first)-w;
        if (val < mns[1] || not mnb[1]){
          mnb[1] = true;
          mns[1] = val;
        }
      } else if (!tl && tr) { //right
        int val = 2*(M[j].first-N[i].first)-w;
        if (val < mns[2] || not mnb[2]){
          mnb[2] = true;
          mns[2] = val;
        }
      } else { // bottom
        int val = 2*(N[i].second-M[j].second)-h;
        if (val < mns[3] || not mnb[3]){
          mnb[3] = true;
          mns[3] = val;
        }
      }
    }
    
    if(mnb[0]){ //top
      lp.set_a(i , c, h);
      lp.set_b(c, mns[0]);
      c++;
    } 
    
    if (mnb[1]) { //left
      lp.set_a(i , c, w);
      lp.set_b(c, mns[1]);
      c++;
    } 
    
    if (mnb[2]) { //right
      lp.set_a(i , c, w);
      lp.set_b(c, mns[2]);
      c++;
    } 
    
    if (mnb[3]) { // bottom
      lp.set_a(i , c, h);
      lp.set_b(c, mns[3]);
      c++;
    }
    
  }
  
  
  
  
  for(int i=0; i<n; ++i){
    for(int j=i+1; j<n; j++){
      bool tr = w*N[i].second - h*N[j].first + h*N[i].first <= w*N[j].second;
      bool tl = w*N[i].second + h*N[j].first - h*N[i].first <= w*N[j].second;

      if(tl && tr){ //top
        lp.set_a(i , c, h);
        lp.set_a(j , c, h);
        lp.set_b(c, 2*(N[j].second-N[i].second));
      } else if (tl && !tr) { //left
        lp.set_a(i , c, w);
        lp.set_a(j , c, w);
        lp.set_b(c, 2*(N[i].first-N[j].first));
      } else if (!tl && tr) { //right
        lp.set_a(i , c, w);
        lp.set_a(j , c, w);
        lp.set_b(c, 2*(N[j].first-N[i].first));
      } else { // bottom
        lp.set_a(i , c, h);
        lp.set_a(j , c, h);
        lp.set_b(c, 2*(N[i].second-N[j].second));
      }
      c++;
    }
  }
  
  for(int i=0; i<n; ++i){
    lp.set_c(i, -2*(w+h));
  }
  
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
  
  std::cout << std::setprecision(0) << std::fixed << floor_to_double(s.objective_value()) << std::endl;

}


int main(){
  
  std::ios::sync_with_stdio(false);
  
  int t;
  std::cin >> t;

  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
  
}
