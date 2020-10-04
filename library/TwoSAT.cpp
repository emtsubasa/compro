// use SCC
struct TwoSAT {
  int n;
  StronglyConnectedComponent scc;
  TwoSAT(int _n = 1) : n(_n), scc(2 * _n) {}
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