// calc min(a*xs[i] + b)
template <class T>
struct LiChaoTree {
  struct Line {
    T a, b;
    Line(T a, T b) : a(a), b(b) {}
    inline T get(T x) const { return a * x + b; }
    inline bool over(const Line &b, const T &x) const {
      return get(x) < b.get(x);
    }
  };
  vector<T> xs;
  vector<Line> seg;
  int xsize;
  LiChaoTree() {}
  LiChaoTree(const vector<T> &x, T INF) : xs(x) {
    xsize = 1;
    while (xsize < xs.size()) xsize <<= 1;
    while (xs.size() < xsize) xs.push_back(xs.back() + 1);
    seg.assign((xsize << 1) - 1, Line(0, INF));
  }
  void update(Line &x, int k, int l, int r) {
    int mid = (l + r) >> 1;
    bool chl = x.over(seg[k], xs[l]), chr = x.over(seg[k], xs[mid]);
    if (chr) swap(seg[k], x);
    if (l + 1 >= r) return;
    if (chl != chr)
      update(x, 2 * k + 1, l, mid);
    else
      update(x, 2 * k + 2, mid, r);
  }
  void update(T a, T b) {
    Line nowl(a, b);
    update(nowl, 0, 0, xsize);
  }
  T query(int k) {
    const T x = xs[k];
    k += xsize - 1;
    T ans = seg[k].get(x);
    while (k > 0) {
      k = (k - 1) >> 1;
      ans = min(ans, seg[k].get(x));
    }
    return ans;
  }
};
