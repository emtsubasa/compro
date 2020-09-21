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

template <class T>
struct Matrix {
  vector<vector<T>> A;
  Matrix() {}
  Matrix(size_t m, size_t n) : A(m, vector<T>(n, 0)) {}
  Matrix(size_t n) : A(n, vector<T>(n, 0)) {}
  size_t height() const { return (A.size()); }
  size_t width() const { return (A[0].size()); }
  inline const vector<T> &operator[](int k) const { return (A.at(k)); }
  inline vector<T> &operator[](int k) { return (A.at(k)); }
  static Matrix E(size_t n) {
    Matrix mat(n);
    for (int i = 0; i < n; ++i) mat[i][i] = 1;
    return (mat);
  }
  Matrix &operator+=(const Matrix &B) {
    size_t m = height(), n = width();
    assert(m == B.height() && n == B.width());
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j) (*this)[i][j] += B[i][j];
    return (*this);
  }
  Matrix &operator-=(const Matrix &B) {
    size_t m = height(), n = width();
    assert(m == B.height() && n == B.width());
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j) (*this)[i][j] -= B[i][j];
    return (*this);
  }
  Matrix &operator*=(const Matrix &B) {
    size_t m = height(), n = B.width(), p = width();
    assert(p == B.height());
    vector<vector<T>> C(m, vector<T>(n, 0));
    for (int i = 0; i < m; ++i)
      for (int k = 0; k < p; ++k) {
        T tmp = (*this)[i][k];
        for (int j = 0; j < n; ++j) C[i][j] += tmp * B[k][j];
      }
    A.swap(C);
    return (*this);
  }
  Matrix &operator^=(long long k) {
    Matrix B = Matrix::E(height());
    while (k) {
      if (k & 1) B *= *this;
      *this *= *this;
      k >>= 1;
    }
    A.swap(B.A);
    return (*this);
  }

  Matrix operator+(const Matrix &B) const { return (Matrix(*this) += B); }
  Matrix operator-(const Matrix &B) const { return (Matrix(*this) -= B); }
  Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }
  Matrix operator^(const long long k) const { return (Matrix(*this) ^= k); }
  friend ostream &operator<<(ostream &os, Matrix &p) {
    size_t m = p.height(), n = p.width();
    for (int i = 0; i < m; i++) {
      os << "[";
      for (int j = 0; j < n; j++) {
        os << p[i][j] << (j + 1 == n ? "]\n" : ",");
      }
    }
    return (os);
  }
};

int q, a, l, r;

ModInt<> calc(int x);

int main() {
  cin >> q;
  for (int i = 0; i < q; ++i) {
    cin >> a >> l >> r;
    cout << calc(r) - calc(l - 1) << endl;
  }
  return 0;
}

ModInt<> calc(int x) {
  if (x < 0) return 0;
  if (a == 1) return x + 1;
  long long b = (long long)a * a - 1;
  Matrix<ModInt<>> mat(4, 4), vec(4, 1);
  mat[0][0] = mat[2][1] = mat[3][3] = vec[0][0] = vec[1][0] = vec[3][0] = 1;
  mat[0][3] = -1;
  mat[0][1] = 2 * a;
  mat[0][2] = 2 * b;
  mat[1][1] = mat[2][2] = a;
  mat[1][2] = b;
  return ((mat ^ x) * vec)[0][0];
}