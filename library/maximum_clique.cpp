using ull = unsigned long long;
inline int trail(ull s) { return (s ? __builtin_ctzll(s) : 64); }
// O(3^(n/3)) ? reference:
// https://sites.google.com/site/indy256/algo/bron_kerbosh
template <typename T>
T BronKerbosch(const vector<ull> &g, ull cur, ull allowed, ull forbidden,
               const vector<T> &w) {
  if (allowed == 0 && forbidden == 0) {
    T res = 0;
    for (int u = trail(cur); u < g.size(); u += trail(cur >> (u + 1)) + 1)
      res += w[u];
    return res;
  }
  if (allowed == 0) return -1;
  T res = -1;
  int piv = trail(allowed | forbidden);
  ull z = allowed & ~g[piv];
  for (int u = trail(z); u < g.size(); u += trail(z >> (u + 1)) + 1) {
    res = max(res, BronKerbosch(g, cur | (1ULL << u), allowed & g[u],
                                forbidden & g[u], w));
    allowed ^= 1ULL << u;
    forbidden |= 1ULL << u;
  }
  return res;
}

template <typename T>
T maximum_clique(const vector<vector<int>> G, const vector<T> &w) {
  int n = G.size();
  assert(n < 64);
  vector<ull> g(n, 0);
  for (int i = 0; i < n; ++i)
    for (int j : G[i]) g[i] ^= 1ULL << j;
  return BronKerbosch<T>(g, 0, (1ULL << n) - 1, 0, w);
}

template <typename T>
T maximal_independent_set(const vector<vector<int>> &G, const vector<T> &w) {
  int n = G.size();
  assert(n < 64);
  vector<ull> g(n, (1ULL << n) - 1);
  for (int i = 0; i < n; ++i) {
    g[i] ^= 1ULL << i;
    for (int j : G[i]) g[i] ^= 1ULL << j;
  }
  return BronKerbosch<T>(g, 0, (1ULL << n) - 1, 0, w);
}
