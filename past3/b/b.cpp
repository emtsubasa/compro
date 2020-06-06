#include <bits/stdc++.h>
using namespace std;

long long q, n, m;
vector<long long> cnt;
vector<vector<long long>> sol;

int main() {
  cin >> n >> m >> q;
  cnt.assign(m, 0);
  sol.resize(n);
  for (int i = 0; i < q; ++i) {
    int x, y, z;
    cin >> x;
    if (x == 1) {
      cin >> y;
      long long res = 0;
      for (auto p : sol[y - 1]) res += n - cnt[p];
      cout << res << endl;
    } else {
      cin >> y >> z;
      --y, --z;
      ++cnt[z];
      sol[y].push_back(z);
    }
  }
  return 0;
}