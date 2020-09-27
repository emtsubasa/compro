vector<int> centroids(const vector<vector<int>> &g) {
  int n = g.size();
  vector<int> sz(n, 0), res;
  auto dfs = [&](int now, int par, auto &&dfs) -> void {
    sz[now] = 1;
    bool ch = true;
    for (auto to : g[now])
      if (to != par) {
        dfs(to, now, dfs);
        if (sz[to] > n / 2) ch = false;
        sz[now] += sz[to];
      }
    if (n - sz[now] > n / 2) ch = false;
    if (ch) res.push_back(now);
  };
  dfs(0, n, dfs);
  return res;
}