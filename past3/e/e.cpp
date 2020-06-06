#include <bits/stdc++.h>
using namespace std;

long long n, m, q;
vector<vector<int>> g;
vector<int> col;

int main() {
  cin >> n >> m >> q;
  g.resize(n);
  col.resize(n);
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    g[--x].push_back(--y);
    g[y].push_back(x);
  }
  for (int i = 0; i < n; ++i) cin >> col[i];
  for (int i = 0; i < q; ++i) {
    int b, x, y;
    cin >> b;
    if (b == 1) {
      cin >> x;
      --x;
      int c = col[x];
      cout << c << endl;
      for (auto p : g[x]) col[p] = c;
    } else {
      cin >> x >> y;
      cout << col[--x] << endl;
      col[x] = y;
    }
  }

  cout << endl;
  return 0;
}