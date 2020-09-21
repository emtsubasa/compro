#include <bits/stdc++.h>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  if ((a == 1) ^ (b - a + 1) & 1)
    cout << "ODD" << endl;
  else
    cout << "EVEN" << endl;
  return 0;
}