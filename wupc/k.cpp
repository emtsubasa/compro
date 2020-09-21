#include <bits/stdc++.h>
using namespace std;

int n, m, z;

int main() {
  cin >> n >> m >> z;
  if ((n & m & 1) || (((n ^ m) & 1) && z >= 2))
    cout << "FIRST" << endl;
  else
    cout << "SECOND" << endl;
  return 0;
}
