#include <bits/stdc++.h>
using namespace std;

long long a, b, c, n, sum = 0;
vector<long long> x;

int main() {
  cin >> a >> b >> c >> n;
  x.resize(n);
  for (int i = 0; i < n; ++i) cin >> x[i];
  for (int i = 0; i < n; ++i) sum += x[i];
  if (10000LL * a + 5000 * b + 1000 * c >= sum)
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
  return 0;
}