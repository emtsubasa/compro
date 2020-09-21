// ModIntR::set_mod()
struct ModIntR {
  int x;
  ModIntR() : x(0) {}
  ModIntR(int64_t y) : x(y >= 0 ? y % mod() : (mod() - (-y) % mod()) % mod()) {}
  static int &mod() {
    static int mod = 0;
    return mod;
  }
  static void set_mod(int md) { mod() = md; }
  ModIntR &operator+=(const ModIntR &p) {
    if ((x += p.x) >= mod()) x -= mod();
    return *this;
  }
  ModIntR &operator-=(const ModIntR &p) {
    if ((x += mod() - p.x) >= mod()) x -= mod();
    return *this;
  }

  ModIntR &operator*=(const ModIntR &p) {
    long long m = mod();
    x = (int)(1LL * x * p.x % m);
    return *this;
  }

  ModIntR &operator/=(const ModIntR &p) {
    *this *= p.inverse();
    return *this;
  }

  ModIntR operator-() const { return ModIntR(-x); }

  ModIntR operator+(const ModIntR &p) const { return ModIntR(*this) += p; }

  ModIntR operator-(const ModIntR &p) const { return ModIntR(*this) -= p; }

  ModIntR operator*(const ModIntR &p) const { return ModIntR(*this) *= p; }

  ModIntR operator/(const ModIntR &p) const { return ModIntR(*this) /= p; }

  bool operator==(const ModIntR &p) const { return x == p.x; }

  bool operator!=(const ModIntR &p) const { return x != p.x; }

  ModIntR inverse() const {
    int a = x, b = mod(), u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModIntR(u);
  }

  ModIntR pow(int64_t n) const {
    ModIntR res(1), mul(x);
    while (n) {
      if (n & 1) res *= mul;
      mul *= mul;
      n >>= 1;
    }
    return res;
  }

  friend ostream &operator<<(ostream &os, const ModIntR &p) {
    return os << p.x;
  }

  friend istream &operator>>(istream &is, ModIntR &a) {
    int64_t t;
    is >> t;
    a = ModIntR(t);
    return (is);
  }
};