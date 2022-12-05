#include <iostream>
#include <vector>
#include <set>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

void solve(){
  int n, m, u, v, k, l;
  std::cin >> m >> n;
  
  std::vector<K::Point_2> P;
  
  for(int i=0; i<m; ++i){
    std::cin >> u >> v;
    
    P.push_back(K::Point_2(u,v));
  }
  
  std::vector<std::vector<K::Line_2>> T;
  
  for(int i=0; i<n; ++i){
    
    double dx = 0;
    double dy = 0;
    
    std::vector<K::Line_2> t;
    
    for (int i=0; i<3; ++i){
      std::cin >> u >> v >> k >> l;
      dx += u;
      dy += v;
      t.push_back(K::Line_2(K::Point_2(u,v), K::Point_2(k,l)));
    }
    
    dx += k;
    dy += l;
    
    dx /= 4;
    dy /= 4;
    
    K::Point_2 ct(dx, dy);
    
    for(int i=0; i<3; ++i){
      if (t[i].has_on_negative_side(ct)){
        t[i] = t[i].opposite();
      }
    }
    
    T.push_back(t);
  }
  
  std::vector<std::set<int>*> mp;
  
  for(int i=0; i<n; ++i){
    mp.push_back(new std::set<int>{});
  }
  
  std::vector<bool> prev(n, false);
  
  for(int i=0; i<n; ++i){
      bool notinside = false;
      for(int h=0; h<3; ++h){
        if (T[i][h].has_on_negative_side(P[0])){
          notinside = true;
          break;
        }
      }
      
      prev[i] = notinside;
  }
  
  for (int j=1; j<m; ++j){
    for (int i=0; i<n; ++i){
      bool inside = true;
      bool newinside = false;
      for(int h=0; h<3; ++h){
        bool temp = T[i][h].has_on_negative_side(P[j]);
        if(temp){
          newinside = true;
          inside = false;
          break;
        }
      }
      if (prev[i]){
        inside = false;
      }
      
      prev[i] = newinside;
      
      if (inside){
        mp[i]->insert(j-1);
      }
    }
  }
  
  int mn = n;
  
  
  int curri = 0;
  int currj = 0;
  
  std::vector<int> counter(m-1,0);
  bool addnew = true;
  while (currj < n){
    if(currj < curri){
      currj++;
      addnew = true;
    }
    
    if (addnew){
      for(int x : *(mp[currj])){
        counter[x]++;
      }
      addnew = false;
    }
    
    bool full = true;
    for(int i=0; i<m-1; ++i){
      if (counter[i] == 0){
        full = false;
        break;
      }
    }
    
    if (full){
      int val = currj-curri+1;
      if (val < mn){
        mn = val;
      }
      
      for(int x : *(mp[curri])){
        counter[x]--;
      }
      curri++;
    } else {
      currj++;
      addnew = true;
    }
  }

  std::cout << mn << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int c;
  std::cin >> c;
  
  for(int i=0; i<c; ++i){
    solve();
  }
  
  return 0;
}
