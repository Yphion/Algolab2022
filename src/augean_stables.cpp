#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void solve(){
  int n;
  cin >> n;
  
  vector<long> Q;
  vector<int> K, L, M;
  
  for(int i=0; i<n; ++i){
    int f, c, k, l, m;
    cin >> f >> c >> k >> l >> m;
    Q.push_back(f-c);
    K.push_back(k);
    L.push_back(l);
    M.push_back(m);

  }
  
  vector<long> A;
  A.push_back(0);
  for(int i=1; i<=24; ++i){
    int a;
    cin >> a;
    A.push_back(a+A[i-1]);
  }
  
  vector<long> P; 
  P.push_back(0);
  for(int i=1; i<=24; ++i){
    int p;
    cin >> p;
    P.push_back(p+P[i-1]);
  }
  
  Program lp (CGAL::SMALLER, true, 0, true, 1); 

  for(int i=0; i<n; ++i){
    lp.set_b(i, -Q[i]);
  }
  
  int ja = 0;
  int jp = 24;
  int opt = 1000;
  
  if(P[24] == 0){
    jp = 0;
  }
  
  while(ja <= 24){
    
    if (jp < 0 || (jp==0  && ja > opt)){
      break;
    }
    
    for(int x = 0; x<n; ++x){
      long k = K[x] + A[ja]*A[ja];
      long l = L[x] + P[jp]*P[jp];
      long m = M[x] + A[ja]*P[jp];
      lp.set_a(0, x, -k);
      lp.set_a(1, x, -l);
      lp.set_a(2, x, -m);
    }
    
    Solution s = CGAL::solve_linear_program(lp, ET());
    
    if (s.is_infeasible()){
      ja++;
    } else {
      opt = min(opt, ja+jp);
      jp--;
    }
  }
  
  if (opt == 1000){
    cout << "Impossible!" << endl;
  } else {
    cout << opt << endl;
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
