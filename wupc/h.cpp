#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> g;
string res, col = "RGB";

vector<int> search_diameter();
void mod_coloring(int now, int par, int dist, int ad = 1);
int calc_dist(int now, int par, int dist);
int solve();

int main() {
  cin >> n;
  g.resize(n);
  res = string(n, '-');
  for (int i = 1; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    g[--a].push_back(--b);
    g[b].push_back(a);
  }
  cout << solve() << endl;
  cout << res << endl;
  return 0;
}

vector<int> search_diameter() {
  vector<int> par;
  int root = 0;
  for (int i = 0; i < 2; ++i) {
    queue<int> qu;
    qu.push(root);
    par.assign(n, -2);
    par[root] = -1;
    while (qu.size()) {
      int now = qu.front();
      root = now;
      qu.pop();
      for (auto to : g[now])
        if (par[to] == -2) {
          par[to] = now;
          qu.push(to);
        }
    }
  }
  vector<int> v;
  while (root != -1) {
    v.push_back(root);
    root = par[root];
  }
  return v;
}

void mod_coloring(int now, int par, int dist, int ad) {
  res[now] = col[dist];
  for (auto to : g[now])
    if (to != par) mod_coloring(to, now, (dist + ad + 3) % 3, ad);
}

int calc_dist(int now, int par, int dist) {
  int res = dist;
  for (auto to : g[now])
    if (to != par) res = max(res, calc_dist(to, now, dist + 1));
  return res;
}

int solve() {
  auto dpath = search_diameter();
  int d = dpath.size();
  if (d & 1) {
    if (d % 3) {
      mod_coloring(0, -1, 0);
      return (d + 2) / 3;
    } else {  // check
      int cnt = 0, root = dpath[d / 2];
      mod_coloring(root, -1, 0);
      mod_coloring(dpath[d / 2 - 1], root, 2, -1);
      for (auto to : g[root])
        if (calc_dist(to, root, 1) == d / 2) ++cnt;
      return (d + 2 + (cnt >= 3)) / 3;
    }
  } else {
    mod_coloring(dpath[d / 2], dpath[d / 2 - 1], 0);
    mod_coloring(dpath[d / 2 - 1], dpath[d / 2], 2, -1);
    return (d + 2) / 3;
  }
  return -1;
}