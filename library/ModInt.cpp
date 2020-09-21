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