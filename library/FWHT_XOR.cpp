template <class T>
struct FWHT_XOR {
  vector<T> multiply(vector<T> a, vector<T> b) {
    int len = 1, n = max(a.size(), b.size());
    while (len < n) len <<= 1;
    a.resize(len), b.resize(len);
    fwht(a), fwht(b);
    for (int i = 0; i < len; ++i) a[i] *= b[i];
    ifwht(a);
    return a;
  }
  void fwht(vector<T> &v) {
    int n = v.size();
    for (int i = 1; i < n; i <<= 1)
      for (int j = 0; j < n; ++j)
        if (!(j & i)) {
          T x = v[j], y = v[j | i];
          v[j] = x + y, v[j | i] = x - y;
        }
  }
  void ifwht(vector<T> &v) {
    int n = v.size();
    for (int i = 1; i < n; i <<= 1)
      for (int j = 0; j < n; ++j)
        if (!(j & i)) {
          T x = v[j], y = v[j | i];
          // mint two = mint(2).inverse();
          v[j] = (x + y) / 2, v[j | i] = (x - y) / 2;
        }
  }
};