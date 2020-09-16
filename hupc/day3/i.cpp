#include <bits/stdc++.h>
using namespace std;

struct Unionfind {
  // tree number
  vector<int> par;
  // constructor
  Unionfind(int n = 1) : par(n, -1) {}
  // search root
  int root(int x) {
    if (par[x] < 0) return x;
    return par[x] = root(par[x]);
  }
  // is same?
  bool issame(int x, int y) { return root(x) == root(y); }

  // add
  // already added, return 0
  bool uni(int x, int y) {
    x = root(x);
    y = root(y);
    if (x == y) return 0;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return 1;
  }
  int size(int x) { return -par[root(x)]; }
};

int n;
vector<long long> a, id;

int main() {
  cin >> n;
  a.resize(n);
  for (auto &p : a) cin >> p;
  Unionfind uf(n + 1);
  id.resize(n);
  iota(id.begin(), id.end(), 0);
  sort(id.begin(), id.end(),
       [](long long l, long long r) { return a[l] < a[r]; });
  long long res = 0;
  for (int i = 0; i < n; ++i) {
    int now = id[i] + 1;
    for (int j = 2; j * now <= n; ++j)
      if (!uf.issame(now, now * j)) {
        uf.uni(now, now * j);
        res += a[id[i]];
      }
  }
  cout << res << endl;
  return 0;
}