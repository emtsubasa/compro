// MOD ver.
#define MOD (long long)(1e9 + 7)
int gauss_jordan(Matrix<ModInt<MOD>> &A, bool is_extended = false) {
  int m = A.height(), n = A.width(), rank = 0;
  for (int col = 0; col < n; ++col) {
    if (is_extended && col == n - 1) break;
    int piv = -1;
    for (int row = rank; row < m; ++row)
      if (A[row][col] != 0) {
        piv = row;
        break;
      }
    if (piv == -1) continue;
    swap(A[piv], A[rank]);
    ModInt<MOD> inv = A[rank][col];
    for (int col2 = 0; col2 < n; ++col2) A[rank][col2] = A[rank][col2] / inv;
    for (int row = 0; row < m; ++row)
      if (row != rank && A[row][col] != 0) {
        ModInt<MOD> fac = A[row][col];
        for (int col2 = 0; col2 < n; ++col2)
          A[row][col2] -= A[rank][col2] * fac;
      }
    ++rank;
  }
  return rank;
}

int linear_equation(Matrix<ModInt<MOD>> A, vector<ModInt<MOD>> b,
                    vector<ModInt<MOD>> &ans) {
  int m = A.height(), n = A.width();
  Matrix<ModInt<MOD>> M(m, n + 1);
  assert((int)b.size() == m);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) M[i][j] = A[i][j];
    M[i][n] = b[i];
  }
  int rank = gauss_jordan(M, 1);
  ans.assign(n, 0);
  for (int i = 0; i < rank; ++i) ans[i] = M[i][n];
  // exist?
  for (int row = rank; row < m; ++row)
    if (M[row][n] != 0) return -1;
  return rank;
}