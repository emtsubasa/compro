#include <bits/stdc++.h>
#define inf (long long)(1e17)
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

struct dat {
  long long u, v, cos;
  bool operator<(const dat& d) const {
    if (cos != d.cos) return cos > d.cos;
    if (u != d.u) return u > d.u;
    return v > d.v;
  }
};

long long n, m, a, b, c, d;
priority_queue<dat> pq, pq2;
Unionfind uf;

long long calc(long long x) {
  long long res = 0;
  long long tmp = min(x, a);
  res += c * tmp;
  x -= tmp;
  tmp = min(x, b);
  res += d * tmp;
  x -= tmp;
  if (x) return inf;
  return res;
}

int main() {
  cin >> n >> m >> a >> b;
  uf = Unionfind(n);
  for (int i = 0; i < m; ++i) {
    int x, y, z;
    cin >> x >> y >> z;
    dat now;
    now.u = x;
    now.v = y;
    now.cos = z;
    pq.push(now);
  }
  cin >> c >> d;
  long long res = inf, cnt = 0, sum = 0;
  if (a >= n - 1) res = (n - 1) * c;
  pq2 = pq;
  while (pq.size()) {
    dat now = pq.top();
    pq.pop();
    if (!uf.issame(now.u, now.v)) {
      ++cnt;
      sum += now.cos;
      uf.uni(now.u, now.v);
    }
    if (a >= n - 1 - cnt) res = min(res, sum + c * (n - 1 - cnt));
  }
  pq = pq2;
  sum = d, cnt = 0;
  --b;
  if (c > d) {
    swap(c, d);
    swap(a, b);
  }
  uf = Unionfind(n);
  while (pq.size()) {
    dat now = pq.top();
    pq.pop();
    if (!uf.issame(now.u, now.v)) {
      ++cnt;
      sum += now.cos;
      uf.uni(now.u, now.v);
    }
    if (a + b >= n - 1 - cnt) res = min(res, sum + calc(n - 1 - cnt));
  }
  if (res == inf)
    cout << -1 << endl;
  else
    cout << res << endl;
  return 0;
}