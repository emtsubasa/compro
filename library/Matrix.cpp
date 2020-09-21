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