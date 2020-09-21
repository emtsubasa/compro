struct HeavyLightDecomposition {
  int root;
  vector<vector<int>> g;
  vector<int> sz, par, dep, in, out, head;
  HeavyLightDecomposition(int n = 1, int _root = 0)
      : root(_root), g(n), sz(n), par(n), dep(n), in(n), out(n), head(n) {}
  HeavyLightDecomposition(const vector<vector<int>> &_g, const int _root = 0)
      : root(_root),
        g(_g),
        sz(_g.size()),
        par(_g.size()),
        dep(_g.size()),
        in(_g.size()),
        out(_g.size()),
        head(_g.size()) {
    build();
  }
  void add(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
  }
  void build() {
    dfs_sz(root, -1, 0);
    int t = 0;
    dfs_hld(root, -1, t);
  }
  void dfs_sz(int now, int bf, int d) {
    dep[now] = d;
    par[now] = bf;
    sz[now] = 1;
    if (g[now].size() && g[now][0] == bf) swap(g[now][0], g[now].back());
    for (auto &to : g[now]) {
      if (to == bf) continue;
      dfs_sz(to, now, d + 1);
      sz[now] += sz[to];
      if (sz[g[now][0]] < sz[to]) swap(g[now][0], to);
    }
  }
  void dfs_hld(int now, int bf, int &t) {
    in[now] = t++;
    for (auto &to : g[now]) {
      if (to == bf) continue;
      head[to] = (g[now][0] == to ? head[now] : to);
      dfs_hld(to, now, t);
    }
    out[now] = t;
  }
  int lca(int x, int y) {
    for (;; y = par[head[y]]) {
      if (in[x] > in[y]) swap(x, y);
      if (head[x] == head[y]) return x;
    }
  }
  int chil(int x, int y) { return dep[x] < dep[y] ? y : x; }
  //[l,r)
  template <typename F>
  void for_each(int x, int y, const F &f) {
    for (;; y = par[head[y]]) {
      if (in[x] > in[y]) swap(x, y);
      f(max(in[head[y]], in[x]), in[y] + 1);
      if (head[x] == head[y]) return;
    }
  }
  //[l,r)
  template <typename F>
  void for_eachedge(int x, int y, const F &f) {
    while (1) {
      if (in[x] > in[y]) swap(x, y);
      if (head[x] != head[y]) {
        f(in[head[y]], in[y] + 1);
        y = par[head[y]];
      } else {
        if (x != y) f(in[x] + 1, in[y] + 1);
        break;
      }
    }
  }
  template <typename T, typename F>
  void update(int node, T x, const F &f) {
    f(in[node], x);
    f(out[node], -x);
    // laze pattern
    // f(in[node], out[node], x);
  }
};