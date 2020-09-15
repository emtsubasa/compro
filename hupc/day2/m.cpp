#include <bits/stdc++.h>
using namespace std;

const int len = 317;

using B = bitset<len + 1>;

int n, k;
vector<vector<int>> g;
vector<int> c;
vector<vector<B>> memo;

bool solve();
void dfs(int now, int par, int &res);

int main() {
  cin >> n >> k;
  c.resize(n);
  for (auto &p : c) {
    cin >> p;
    p &= 1;
  }
  g.resize(n);
  for (int i = 1; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  if (solve())
    cout << "Aizu" << endl;
  else
    cout << "Beet" << endl;
  return 0;
}

bool solve() {
  memo.resize(n, vector<B>(k + 1, 0));
  int res = 0;
  dfs(0, -1, res);
  return res;
}
void dfs(int now, int par, int &res) {
  for (auto to : g[now])
    if (to != par) {
      dfs(to, now, res);
      for (int i = 1; i <= k; ++i) memo[now][i] |= memo[to][i - 1];
    }
  B nb;
  for (auto b : memo[now]) nb |= b;
  for (int i = 0; i <= len; ++i)
    if (!nb[i]) {
      memo[now][0][i] = 1;
      if (c[now] & 1) res ^= i;
      break;
    }
}