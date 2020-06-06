#include <bits/stdc++.h>
using namespace std;

long long n, m;
vector<long long> dp;

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    long long a;
    cin >> a;
    auto it = upper_bound(dp.begin(), dp.end(), a, greater<long long>());
    if (it == dp.end()) {
      if (dp.size() == n)
        cout << -1 << endl;
      else {
        dp.push_back(a);
        cout << dp.size() << endl;
      }
    } else {
      cout << (it - dp.begin()) + 1 << endl;
      *it = a;
    }
  }
  return 0;
}