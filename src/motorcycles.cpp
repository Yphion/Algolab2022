#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <CGAL/Gmpq.h>

typedef CGAL::Gmpq Q;

struct Bike {
  long y;
  int i;
  Q r;
  
  Bike (long xy, int xi, Q xr){
    y = xy;
    i = xi;
    r = xr;
  }
  
  bool operator< (const Bike &other){
    return (y < other.y);
  }
};

void solve(){
  
  int n;
  std::cin >> n;
  
  long y, dx, dy;
  
  std::vector<Bike> R;
  R.reserve(n);
  
  for(int i=0; i<n; ++i){
    std::cin >> y >> dx >> dy;
    
    R.push_back(Bike(y, i, Q(dy-y, dx)));
  }
  
  std::sort(R.begin(), R.end());
  
  std::vector<bool> S(n, true);
  
  Q opt = R[0].r;
  
  for(int i=1; i<n; ++i){
    
    Q val = R[i].r;
    
    if ( abs(val) < abs(opt) || (abs(val) == abs(opt) && val >= opt)){
      opt = val;
    } else if(val < opt){
      S[R[i].i] = false;
    }
    
  }
  
  opt = R[n-1].r;
  
  for(int i=n-2; i>=0; --i){
    
    Q val = R[i].r;
    
    if (abs(val) <= abs(opt)){
      opt = val;
    } else if(val > opt){
      S[R[i].i] = false;
    }
    
  }
  
  
  for (int i=0; i<n; ++i){
    if (S[i])
      std::cout << i << " ";
  }
  std::cout << std::endl;
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
