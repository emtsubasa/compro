struct LCA {
  int n, root, h;
  vector<vector<int>> g, par;
  vector<int> dep;
  LCA(int _n = 1, int r = 0) : n(_n), root(r), g(_n), dep(_n) {
    h = 1;
    while ((1 << h) <= n) ++h;
    par.assign(h, vector<int>(n, -1));
  }
  LCA(const vector<vector<int>> &_g, const int r = 0)
      : n(_g.size()), root(r), g(_g), dep(_g.size()) {
    h = 1;
    while ((1 << h) <= n) ++h;
    par.assign(h, vector<int>(n, -1));
    build();
  }
  void add(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
  }
  void dfs(int now, int bf, int d) {
    par[0][now] = bf;
    dep[now] = d;
    for (int &to : g[now])
      if (to != bf) dfs(to, now, d + 1);
  }
  void build() {
    dfs(root, -1, 0);
    for (int i = 0; i + 1 < h; ++i)
      for (int j = 0; j < n; ++j) {
        if (par[i][j] < 0)
          par[i + 1][j] = -1;
        else
          par[i + 1][j] = par[i][par[i][j]];
      }
  }
  int calc(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    for (int i = 0; i < h; ++i)
      if ((dep[y] - dep[x]) >> i & 1) y = par[i][y];
    if (x == y) return x;
    for (int i = h - 1; i >= 0; --i)
      if (par[i][x] != par[i][y]) {
        x = par[i][x];
        y = par[i][y];
      }
    return par[0][y];
  }

  inline int dist(int x, int y) {
    return dep[x] + dep[y] - 2 * dep[calc(x, y)];
  }

  inline int operator[](const int &k) { return (dep.at(k)); }
};
