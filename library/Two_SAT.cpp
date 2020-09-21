struct Strongly_Connected_Component {
  int n, k;
  vector<vector<int>> G, reverseG;
  vector<int> vs, cmp;
  vector<bool> used;
  Strongly_Connected_Component(int newv = 1) {
    n = newv;
    G.resize(n);
    reverseG.resize(n);
    used.resize(n, 0);
    cmp.resize(n);
  }

  bool add(int from, int to) {
    G[from].push_back(to);
    reverseG[to].push_back(from);
    return 1;
  }
  void dfs(int v) {
    used[v] = true;
    for (auto to : G[v])
      if (!used[to]) dfs(to);
    vs.push_back(v);
  }
  void rdfs(int v) {
    used[v] = true;
    cmp[v] = k;
    for (auto to : reverseG[v])
      if (!used[to]) rdfs(to);
  }
  int solve() {
    used.assign(n, 0);
    vs.clear();
    for (int v = 0; v < n; ++v)
      if (!used[v]) dfs(v);
    used.assign(n, 0);
    k = 0;
    for (int i = (int)vs.size() - 1; i >= 0; --i)
      if (!used[vs[i]]) {
        rdfs(vs[i]);
        ++k;
      }
    return k;
  }
  vector<vector<int>> make_graph(bool dosolve = 1) {
    if (dosolve) solve();
    vector<vector<int>> res(k);
    for (int i = 0; i < n; ++i)
      for (int to : G[i])
        if (!issame(i, to)) res[cmp[i]].push_back(cmp[to]);
    for (auto& v : res) {
      sort(v.begin(), v.end());
      v.erase(unique(v.begin(), v.end()), v.end());
    }
    return res;
  }
  vector<vector<int>> make_list(bool dosolve = 1) {
    if (dosolve) solve();
    vector<vector<int>> res(k);
    for (int i = 0; i < n; ++i) res[cmp[i]].push_back(i);
    return res;
  }
  bool issame(int l, int r) { return cmp[l] == cmp[r]; }
};

struct Two_SAT {
  int n;
  Strongly_Connected_Component scc;
  Two_SAT(int _n = 1) : n(_n), scc(2 * _n) {}
  // a v c : !a -> c && !c -> a
  void add(int a, bool b, int c, bool d) {
    scc.add(a + b * n, c + (!d) * n);
    scc.add(c + d * n, a + (!b) * n);
  }
  bool solve() {
    scc.solve();
    for (int i = 0; i < n; ++i)
      if (scc.cmp[i] == scc.cmp[i + n]) return 0;
    return 1;
  }
  vector<bool> make_vec() {
    vector<bool> res;
    if (!solve()) return res;
    res.assign(n, 0);
    for (int i = 0; i < n; ++i) res[i] = scc.cmp[i] > scc.cmp[i + n];
    return res;
  }
};