struct UnionfindP {
  using P = pair<int, int>;
  vector<int> par, last;
  vector<vector<P>> hist;
  UnionfindP(int n = 1) : par(n, -1), last(n, -1), hist(n) {
    for (auto& v : hist) v.emplace_back(-1, -1);
  }
  int root(int t, int x) {
    if (last[x] == -1 || t < last[x]) return x;
    return root(t, par[x]);
  }
  bool issame(int t, int x, int y) { return root(t, x) == root(t, y); }
  bool uni(int t, int x, int y) {
    x = root(t, x), y = root(t, y);
    if (x == y) return 0;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    last[y] = t;
    hist[x].emplace_back(t, par[x]);
    return 1;
  }
  int size(int t, int x) {
    x = root(t, x);
    return -prev(lower_bound(hist[x].begin(), hist[x].end(), P(t, 0)))->second;
  }
};