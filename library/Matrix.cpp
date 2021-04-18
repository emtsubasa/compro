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

  Matrix trans() {
    size_t m = height(), n = width();
    Matrix res(n, m);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) res[i][j] = (*this)[j][i];
    return res;
  }

  Matrix inv() {
    assert(height() == width());
    size_t n = height();
    Matrix B(n, 2 * n);
    for (int i = 0; i < n; ++i) {
      B[i][i + n] = 1;
      for (int j = 0; j < n; ++j) B[i][j] = (*this)[i][j];
    }
    for (int i = 0; i < n; ++i) {
      int piv = i;
      for (int j = i; j < n; ++j)
        if (abs(B[j][i]) > abs(B[piv][i])) piv = j;
      // not exist or unique
      assert(abs(B[piv][i]) >= 0);
      swap(B[i], B[piv]);
      for (int j = i + 1; j < 2 * n; ++j) B[i][j] /= B[i][i];
      for (int j = 0; j < n; ++j)
        if (i != j)
          for (int k = i + 1; k < 2 * n; ++k) B[j][k] -= B[j][i] * B[i][k];
    }
    Matrix res(n);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) res[i][j] = B[i][j + n];
    return res;
  }

  T det() {
    int m = height(), n = width();
    assert(m == n);
    T res = 1;
    Matrix B(m);
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j) B[i][j] = (*this)[i][j];
    for (int i = 0; i < n; ++i) {
      int piv = i;
      for (int j = i + 1; j < m; ++j)
        if (B[j][i] != 0) {
          piv = j;
          break;
        }
      // if (abs(B[j][i]) > abs(B[piv][i])) piv = j;
      if (B[piv][i] == 0) return (T)0;
      // if (abs(B[piv][i]) < EPS) return (T)0;  // B[piv][i] < EPS
      if (piv != i) swap(B[i], B[piv]), res = -res;
      res *= B[i][i];
      // for (int j = i + 1; j < m; ++j)
      //   for (int k = n - 1; k >= i; --k) B[j][k] -= B[i][k] * B[j][i] /
      //   B[i][i];
      {
        const T d = (T)1 / B[i][i];
        for (int j = i + 1; j < n; ++j) B[i][j] *= d;
        for (int j = i + 1; j < m; ++j)
          for (int k = i + 1; k < n; ++k) B[j][k] -= B[i][k] * B[j][i];
      }
    }
    return res;
  }

  T cofactor(int r = -1, int c = -1) {
    int m = height(), n = width();
    if (r < 0) r = c = m - 1;
    assert(m == n && m > 1 && r < m && c < n);
    Matrix mat(m - 1, n - 1);
    for (int i = 0, rcnt = 0; i < m; ++i)
      if (i != r) {
        int ccnt = 0;
        for (int j = 0; j < n; ++j)
          if (j != c) mat[rcnt][ccnt++] = (*this)[i][j];
        ++rcnt;
      }
    T res = mat.det();
    if ((r ^ c) & 1) res *= -1;
    return res;
  }

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