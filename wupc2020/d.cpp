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
  SegmentTree(const vector<T>& v, F f, T t) : f(f), unit(t) {
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

// as + bt = GCD(a,b) a,b:const s,t:var(any)
// return GCD(a,b)
long long extGCD(long long a, long long b, long long& s, long long& t) {
  s = 1, t = 0;
  long long u = 0, v = 1;
  while (b) {
    long long tmp = a / b;
    a -= b * tmp;
    s -= u * tmp;
    t -= v * tmp;
    swap(s, u);
    swap(t, v);
    swap(a, b);
  }
  return a;
}
// (mod)x+ay=1, calculate y -> a^-1 (mod m) (a,m : coprime)
long long calcinv(long long a, long long m) {
  long long s, t;
  extGCD(a, m, s, t);
  return (s + m) % m;
}

long long mod_pow(long long base, int e, int mod) {
  long long res = 1;
  while (e) {
    if (e & 1) (res *= base) %= mod;
    (base *= base) %= mod;
    e >>= 1;
  }
  return res;
}

int n, m, q, all = 1;
SegmentTree<int> seg;

int main() {
  cin >> n >> m >> q;
  {  // input and pre calc
    auto f = [](int l, int r) { return 1LL * l * r % n; };
    vector<int> v(m, 0);
    for (auto& p : v) {
      cin >> p;
      p = calcinv(p, n);
      all = 1LL * all * p % n;
    }
    for (int i = 0; i < m; ++i) v.push_back(v[i]);
    seg = SegmentTree<int>(v, f, 1);
  }
  for (int i = 0; i < q; ++i) {
    int x, y, z, e;
    cin >> x >> y >> z;
    --y;
    e = 1LL * mod_pow(all, z / m, n) * seg.query(y, y + z % m) % n;
    cout << mod_pow(x, e, n + 1) << endl;
  }
  return 0;
}
