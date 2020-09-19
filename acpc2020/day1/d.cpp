#include <bits/stdc++.h>
using namespace std;

template <int mod = (int)(1e9 + 7)>
struct ModInt {
  int x;
  constexpr ModInt() : x(0) {}
  constexpr ModInt(int64_t y)
      : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
  constexpr ModInt &operator+=(const ModInt &p) noexcept {
    if ((x += p.x) >= mod) x -= mod;
    return *this;
  }
  constexpr ModInt &operator-=(const ModInt &p) noexcept {
    if ((x += mod - p.x) >= mod) x -= mod;
    return *this;
  }
  constexpr ModInt &operator*=(const ModInt &p) noexcept {
    x = (int)(1LL * x * p.x % mod);
    return *this;
  }
  constexpr ModInt &operator/=(const ModInt &p) noexcept {
    *this *= p.inverse();
    return *this;
  }
  constexpr ModInt operator-() const { return ModInt(-x); }
  constexpr ModInt operator+(const ModInt &p) const noexcept {
    return ModInt(*this) += p;
  }
  constexpr ModInt operator-(const ModInt &p) const noexcept {
    return ModInt(*this) -= p;
  }
  constexpr ModInt operator*(const ModInt &p) const noexcept {
    return ModInt(*this) *= p;
  }
  constexpr ModInt operator/(const ModInt &p) const noexcept {
    return ModInt(*this) /= p;
  }
  constexpr bool operator==(const ModInt &p) const noexcept { return x == p.x; }
  constexpr bool operator!=(const ModInt &p) const noexcept { return x != p.x; }
  constexpr ModInt inverse() const noexcept {
    int a = x, b = mod, u = 1, v = 0, t = 0;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModInt(u);
  }
  constexpr ModInt pow(int64_t n) const {
    ModInt res(1), mul(x);
    while (n) {
      if (n & 1) res *= mul;
      mul *= mul;
      n >>= 1;
    }
    return res;
  }
  friend constexpr ostream &operator<<(ostream &os, const ModInt &p) noexcept {
    return os << p.x;
  }
  friend constexpr istream &operator>>(istream &is, ModInt &a) noexcept {
    int64_t t = 0;
    is >> t;
    a = ModInt<mod>(t);
    return (is);
  }
  constexpr int get_mod() { return mod; }
};

// 0-indexed
template <class T>
struct BIT {
  int treesize;
  vector<T> lst;
  // constructor
  BIT(int newn = 0) : treesize(newn), lst(newn + 1, 0) {}
  // a_place += num
  void add(int place, T num) {
    ++place;
    while (place <= treesize) {
      lst[place] += num;
      place += place & -place;
    }
  }
  // sum between [0,place)
  T sum(int place) {
    T res = 0;
    while (place > 0) {
      res += lst[place];
      place -= place & -place;
    }
    return res;
  }
  // sum [l,r)
  T sum(int left, int right) { return sum(right) - sum(left); }
};

int n;
vector<vector<int>> a;
map<int, int> id;
BIT<ModInt<>> dp;

ModInt<> solve();

int main() {
  cin >> n;
  a.resize(n);
  {
    vector<int> v;
    for (int i = 0; i < n; ++i) {
      int m;
      cin >> m;
      a[i].resize(m);
      for (auto &p : a[i]) {
        cin >> p;
        v.push_back(p);
      }
      sort(a[i].begin(), a[i].end());
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int len = v.size();
    for (int i = 1; i <= len; ++i) id[v[i - 1]] = i;
  }
  cout << solve() << endl;
  return 0;
}

ModInt<> solve() {
  dp = BIT<ModInt<>>(id.size() + 1);
  dp.add(0, 1);
  for (int i = 0; i < n; ++i) {
    int m = a[i].size();
    for (int j = m - 1; j >= 0; --j) {
      int now = id[a[i][j]];
      dp.add(now, dp.sum(now));
    }
  }
  return dp.sum(id.size() + 1);
}