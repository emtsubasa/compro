// TwoEdgeConnectedComponents + LowLink
struct TwoEdgeConnectedComponents {
  int n;
  vector<vector<int>> g;
  vector<int> ord, low, articulation, id;
  vector<bool> used;
  using P = pair<int, int>;
  vector<P> bridge;
  TwoEdgeConnectedComponents(int _n = 1) : n(_n), g(n) {}
  TwoEdgeConnectedComponents(vector<vector<int>> &_g) : n(_g.size()), g(_g) {
    lowlinkbuild();
  }

  bool add(int from, int to) {
    g[from].push_back(to);
    g[to].push_back(from);
    return 1;
  }

  void lowlinkbuild() {
    ord.assign(n, -1);
    low.assign(n, -1);
    int k = 0;
    for (int i = 0; i < n; ++i)
      if (ord[i] < 0) lowlinkdfs(i, -1, k);
    sort(articulation.begin(), articulation.end());
  }
  void lowlinkdfs(int now, int par, int &k) {
    ord[now] = low[now] = k++;
    bool ch = 0;  // articulation
    int cnt = 0;
    for (auto &to : g[now])
      if (ord[to] < 0) {
        ++cnt;
        lowlinkdfs(to, now, k);
        low[now] = min(low[now], low[to]);
        ch |= ~par && low[to] >= ord[now];  // articulation
        if (ord[now] < low[to])
          bridge.emplace_back(min(now, to), max(now, to));  // bridge
      } else if (to != par)
        low[now] = min(low[now], ord[to]);
    ch |= par == -1 && cnt > 1;           // articulation
    if (ch) articulation.push_back(now);  // articulation
  }

  vector<vector<int>> build() {
    id.assign(n, -1);
    int k = 0;
    for (int i = 0; i < n; ++i)
      if (id[i] < 0) dfs(i, -1, k);
    vector<vector<int>> res(k);
    for (auto &e : bridge) {
      int x = id[e.first], y = id[e.second];
      res[x].push_back(y);
      res[y].push_back(x);
    }
    return res;
  }

  void dfs(int now, int par, int &k) {
    if (~par && ord[par] >= low[now])
      id[now] = id[par];
    else
      id[now] = k++;
    for (auto &to : g[now])
      if (id[to] < 0) dfs(to, now, k);
  }

  inline int operator[](const int &k) { return (id.at(k)); }
};