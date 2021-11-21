// 0-indexed
template <class T>
struct SegmentTree_2d {
  // a,b,c: T, e:T(unit)
  // abc = (ab)c = a(bc)
  // ae = ea = a
  typedef function<T(T, T)> F;
  int h, w;
  F f;
  T unit;
  vector<vector<T>> dat;
  SegmentTree_2d(){};
  SegmentTree_2d(int _h, int _w, F f, T t) : f(f), unit(t) { init(_h, _w); }
  SegmentTree_2d(const vector<vector<T>> &v, F f, T t) : f(f), unit(t) {
    int _h = v.size(), _w = _h ? v[0].size() : 0;
    init(_h, _w);
    for (int i = 0; i < _h; ++i) {
      for (int j = 0; j < _w; ++j) dat[h + i][w + j] = v[i][j];
      for (int j = w - 1; j; --j)
        dat[h + i][j] = f(dat[h + i][j << 1], dat[h + i][(j << 1) | 1]);
    }
    for (int i = h - 1; i; --i)
      for (int j = (w << 1) - 1; j; --j)
        dat[i][j] = f(dat[i << 1][j], dat[(i << 1) | 1][j]);
  }
  void init(int _h, int _w) {
    h = 1, w = 1;
    while (h < _h) h <<= 1;
    while (w < _w) w <<= 1;
    dat.assign(h << 1, vector<T>(w << 1, unit));
  }

  // "go up" process
  void update(int r, int c, T newdata) {
    dat[r += h][c += w] = newdata;
    while (r) {
      int k = c;
      while (k >>= 1) dat[r][k] = f(dat[r][k << 1], dat[r][(k << 1) | 1]);
      r >>= 1, dat[r][c] = f(dat[r << 1][c], dat[(r << 1) | 1][c]);
    }
  }
  // [u,d) && [l,r)
  T query(int u, int d, int l, int r) {
    T vl = unit, vr = unit;
    for (int a = u + h, b = d + h; a < b; a >>= 1, b >>= 1) {
      if (a & 1) vl = f(vl, query_in(a++, l, r));
      if (b & 1) vr = f(query_in(--b, l, r), vr);
    }
    return f(vl, vr);
  }
  // [a,b)
  T query_in(int id, int a, int b) {
    T vl = unit, vr = unit;
    for (int l = a + w, r = b + w; l < r; l >>= 1, r >>= 1) {
      if (l & 1) vl = f(vl, dat[id][l++]);
      if (r & 1) vr = f(dat[id][--r], vr);
    }
    return f(vl, vr);
  }
};