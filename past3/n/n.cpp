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

using P = pair<long long, long long>;
long long n, q;
vector<int> a;
SegmentTree<P> seg;

int main() {
  auto h = [](P l, P r) {
    return P(l.first + r.first, min(l.second, r.second));
  };
  cin >> n >> q;
  seg = SegmentTree<P>(n + 1, h, P(0, n + 2));
  for (int i = 0; i < n; ++i) a.push_back(i);
  for (int i = 0; i < q; ++i) {
    int t, x, y;
    cin >> t >> x >> y;
    if (t == 1) {
      swap(a[x - 1], a[x]);
      seg.update(x - 1, P(1, x - 1));
      seg.update(x, P(1, x));
    } else {
      for (int l = seg.query(x - 1, y).second; l < y;) {
        int r = y;
        if (seg.query(l, r).first != r - l) {
          int ll = l + 1;
          while (r - ll > 1) {
            int mid = (ll + r) / 2;
            if (seg.query(l, mid).first != mid - l)
              r = mid;
            else
              ll = mid;
          }
          r = ll;
        }
        sort(a.begin() + l, a.begin() + r);
        for (int j = l; j < r; ++j)
          if (a[j] == j) seg.update(j, P(0, n + 2));
        l = seg.query(r, y).second;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    if (i != 0) cout << " ";
    cout << a[i] + 1;
  }
  cout << endl;
  return 0;
}