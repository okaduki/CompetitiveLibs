#include <bits/stdc++.h>

using namespace std;

int main(){
  assert(0b00000001 == 0x01);

  int a = 0, b = 1;
  decltype(auto) d = a + b;
  assert(d == 1);

  return 0;
}
