#include <bits/stdc++.h>
using namespace std;

// 0-indexed
template <class T>
struct SegmentTree {
  // a,b,c: T, e:T(unit)
  // abc = (ab)c = a(bc)
  // ae = ea = a
  typedef function<T(T, T)> F;
  int n;
  F f;
  T unit;
  vector<T> dat;
  SegmentTree(){};
  SegmentTree(int newn, F f, T t) : f(f), unit(t) { init(newn); }
  SegmentTree(const vector<T> &v, F f, T t) : f(f), unit(t) {
    int _n = v.size();
    init(v.size());
    for (int i = 0; i < _n; ++i) dat[n + i] = v[i];
    for (int i = n - 1; i; --i) dat[i] = f(dat[i << 1], dat[(i << 1) | 1]);
  }
  void init(int newn) {
    n = 1;
    while (n < newn) n <<= 1;
    dat.assign(n << 1, unit);
  }

  // "go up" process
  void update(int k, T newdata) {
    dat[k += n] = newdata;
    while (k >>= 1) {
      dat[k] = f(dat[(k << 1) | 0], dat[(k << 1) | 1]);
    }
  }
  // [a,b)
  T query(int a, int b) {
    T vl = unit, vr = unit;
    for (int l = a + n, r = b + n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) vl = f(vl, dat[l++]);
      if (r & 1) vr = f(dat[--r], vr);
    }
    return f(vl, vr);
  }
};

long long n, m;
vector<vector<long long>> t;

int main() {
  cin >> n;
  t.resize(n);
  for (int i = 0; i < n; ++i) {
    int k;
    cin >> k;
    for (int j = 0; j < k; ++j) {
      long long x;
      cin >> x;
      t[i].push_back(x);
    }
    t[i].push_back(-1);
    reverse(t[i].begin(), t[i].end());
  }
  using P = pair<long long, int>;
  auto f = [](P l, P r) { return max(l, r); };
  SegmentTree<P> pre(n, f, P(-1, -1)), suf(n, f, P(-1, -1));
  for (int i = 0; i < n; ++i) {
    pre.update(i, P(t[i].back(), i));
    t[i].pop_back();
  }
  for (int i = 0; i < n; ++i) {
    suf.update(i, P(t[i].back(), i));
    if (t[i].back() >= 0) t[i].pop_back();
  }
  cin >> m;
  for (int i = 0; i < m; ++i) {
    int a;
    cin >> a;
    P now = pre.query(0, n), nows = suf.query(0, n);
    if (a == 1 || now.first > nows.first) {
      cout << now.first << endl;
      P nextp = suf.query(now.second, now.second + 1);
      pre.update(now.second, P(nextp.first, now.second));
      suf.update(now.second, P(t[now.second].back(), now.second));
      if (t[now.second].back() >= 0) t[now.second].pop_back();
    } else {
      cout << nows.first << endl;
      suf.update(nows.second, P(t[nows.second].back(), nows.second));
      if (t[nows.second].back() >= 0) t[nows.second].pop_back();
    }
  }
  return 0;
}