#include <bits/stdc++.h>
using namespace std;

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

long long n, m;
vector<long long> a;

bool solve();

int main() {
  cin >> n >> m;
  a.resize(n);
  for (auto& p : a) {
    cin >> p;
    p %= m;
  }
  if (solve())
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
  return 0;
}

bool solve() {
  Strongly_Connected_Component scc(m);
  for (int i = 0; i < m; ++i)
    for (auto p : a) scc.add(i, i * p % m);
  auto g = scc.make_graph();
  int k = g.size();
  vector<int> dist(k, 100000000);
  dist[scc.cmp[1]] = 0;
  queue<int> qu;
  qu.push(scc.cmp[1]);
  while (qu.size()) {
    int now = qu.front();
    qu.pop();
    for (auto to : g[now])
      if (dist[now] + 1 < dist[to]) {
        dist[to] = dist[now] + 1;
        qu.push(to);
      }
  }
  return dist[scc.cmp[0]] + 1 == k;
}