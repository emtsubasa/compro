#include <bits/stdc++.h>
using namespace std;

long long d, u, k, v;

int main() {
  cin >> d >> u >> k >> v;
  long long a = v * d, b = u * v * k + u * d;
  if (a > b)
    cout << "bus" << endl;
  else if (a < b)
    cout << "bike" << endl;
  else
    cout << "same" << endl;
  return 0;
}