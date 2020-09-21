struct EulerTour {
  int n, root;
  vector<vector<int>> g;
  vector<int> par, dep, in, out, lst;
  EulerTour(int n = 1, int _root = 0)
      : root(_root), g(n), par(n), dep(n), in(n), out(n) {}
  EulerTour(const vector<vector<int>> &_g, const int _root = 0)
      : root(_root),
        g(_g),
        par(_g.size()),
        dep(_g.size()),
        in(_g.size()),
        out(_g.size()) {
    build();
  }
  void add(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
  }
  void build() {
    lst.clear();
    dfs(root, -1, 0);
  }
  void dfs(int now, int bf, int d) {
    dep[now] = d;
    par[now] = bf;
    in[now] = lst.size();
    lst.push_back(now);
    for (auto &to : g[now])
      if (to != bf) {
        dfs(to, now, d + 1);
        lst.push_back(now);  // edge ver.
      }
    if (lst.back() != now) lst.push_back(now);  // edge ver.
    out[now] = lst.size();
  }
  int chil(int x, int y) { return dep[x] < dep[y] ? y : x; }
  template <typename T, typename F>
  void update(int node, T x, const F &f) {
    f(in[node], x);
    f(out[node], -x);
    // laze pattern
    // f(in[node],out[node],x);
  }
  // u-v(lca:r) edge path: [in[r] + 1,in[v] + 1) + [in[r] + 1, in[u] + 1)
};