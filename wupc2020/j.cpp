#include <bits/stdc++.h>
using namespace std;

int n, m, q;
vector<vector<int>> g, rg;
vector<bool> reachable;

void update(int x);

int main() {
  cin >> n >> m;
  g.resize(n);
  rg.resize(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    g[--a].push_back(--b);
    rg[b].push_back(a);
  }
  reachable.assign(n, 0);
  update(0);
  cin >> q;
  while (q--) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    if (x)
      cout << (reachable[y] ? "YES" : "NO") << endl;
    else
      update(y);
  }
  return 0;
}

void update(int x) {
  queue<int> qu;
  qu.push(x);
  if (reachable[x]) return;
  reachable[x] = 1;
  while (qu.size()) {
    int now = qu.front();
    qu.pop();
    reachable[now] = 1;
    for (auto to : rg[now])
      if (!reachable[to]) {
        reachable[to] = 1;
        qu.push(to);
      }
  }
}