#include <bits/stdc++.h>
using namespace std;

int B = 350;
using P = pair<int, int>;
long long n, q;
vector<P> e;
vector<set<int>> g;
vector<long long> cnt, neigh;

int main() {
  cin >> n >> q;
  e.resize(q);
  for (auto &p : e) {
    cin >> p.first >> p.second;
    --p.first, --p.second;
  }
  g.resize(n);
  cnt.assign(n, 0);
  neigh.assign(n, 0);
  long long res = 0;
  for (int i = 0; i < q; i += B) {
    vector<set<int>> ng(n);
    {
      vector<bool> used(n, 0);
      for (int j = i; j < q && j - i < B; ++j)
        used[e[j].first] = used[e[j].second] = 1;
      for (int j = 0; j < n; ++j) {
        neigh[j] = 0;
        for (auto to : g[j]) {
          neigh[j] += cnt[to];
          if (used[j] && used[to]) ng[j].insert(to);
        }
      }
    }
    for (int j = i; j < q && j - i < B; ++j) {
      auto [u, v] = e[j];
      if (g[u].count(v)) {
        neigh[u] -= cnt[v];
        neigh[v] -= cnt[u];
        for (auto to : ng[u])
          if (v != to) --neigh[to];
        for (auto to : ng[v])
          if (u != to) --neigh[to];
        res -= cnt[u]-- * cnt[v]-- + neigh[u] + neigh[v];
        g[u].erase(v);
        g[v].erase(u);
        ng[u].erase(v);
        ng[v].erase(u);
      } else {
        res += ++cnt[u] * ++cnt[v] + neigh[u] + neigh[v];
        g[u].insert(v);
        g[v].insert(u);
        ng[u].insert(v);
        ng[v].insert(u);
        for (auto to : ng[u])
          if (v != to) ++neigh[to];
        for (auto to : ng[v])
          if (u != to) ++neigh[to];
        neigh[u] += cnt[v];
        neigh[v] += cnt[u];
      }
      cout << res << endl;
    }
  }

  return 0;
}