// O(n^2)  P(x_i) = y_i(i:[0,n])
//  calc c_i : P(x) = c_n x^n + c_(n-1) x^(n-1)...c_0
template <typename T>
vector<T> lagrange_interpolation(vector<T> &y, vector<T> &x) {
  assert(y.size() == x.size());
  long long n = y.size();
  vector<T> res(n, 0), Q(n), c[2];
  for (int i = 0; i < 2; ++i) c[i] = vector<T>(n, 0);
  c[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    T inv = 1;
    for (int j = 0; j < n; ++j)
      if (j != i) inv *= x[i] - x[j];
    Q[i] = y[i] / inv;
    for (int j = 0; j < n; ++j) {
      c[(i + 1) % 2][j] = c[i % 2][j] * -x[i];
      if (j != 0) c[(i + 1) % 2][j] += c[i % 2][j - 1];
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = n - 1; j >= 0; --j) {
      if (j == n - 1)
        c[(n + 1) % 2][j] = 1;
      else
        c[(n + 1) % 2][j] = c[n % 2][j + 1] + c[(n + 1) % 2][j + 1] * x[i];
      res[j] += c[(n + 1) % 2][j] * Q[i];
    }
  }
  return res;
}

// O(n log mod) calc f(t) x_i = a + i * d, f(y_i) = y_i
template <typename T>
T lagrange_interpolation(const vector<T> &y, const T &t, const T &a = 0,
                         const T &d = 1) {
  long long n = y.size();
  T res = 0, p = 1;
  for (int i = 1; i < n; ++i) {
    p *= t - (a + d * i);
    p /= -d * i;
  }
  for (int i = 0; i < n; ++i) {
    if (t == a + d * i) return y[i];
    res += y[i] * p;
    p *= t - (a + d * i);
    p /= t - d * (i + 1);
    p *= d * (i - (n - 1));
    p /= d * (i + 1);
  }
  return res;
}