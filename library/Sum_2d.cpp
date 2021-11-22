// 0-indexed
template <class T>
struct Sum_2d {
  int h, w;
  vector<vector<T>> v;
  Sum_2d() {}
  Sum_2d(const vector<vector<T>> &_v) : v(_v) {
    h = v.size(), w = h ? v[0].size() : 0;
    for (int i = 0; i < h; ++i)
      for (int j = 0; j < w; ++j) {
        if (i) v[i][j] += v[i - 1][j];
        if (j) v[i][j] += v[i][j - 1];
        if (i && j) v[i][j] -= v[i - 1][j - 1];
      }
  }
  // sum v[i][j] (u <= i <= d, l <= j <= r)
  T calc(int u, int d, int l, int r) {
    T res = v[d][r];
    if (l) res -= v[d][l - 1];
    if (u) res -= v[u - 1][r];
    if (l && u) res += v[u - 1][l - 1];
    return res;
  }
};