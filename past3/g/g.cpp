#include <bits/stdc++.h>
using namespace std;

int ofst = 500;
int inf = 10000000;

int dx[] = {1, 0, -1, 1, -1, 0};
int dy[] = {1, 1, 1, 0, 0, -1};
int n, gx, gy;
vector<vector<long long>> dist;

int main() {
  cin >> n >> gx >> gy;
  gx += ofst;
  gy += ofst;
  dist.assign(1000, vector<long long>(1000, inf));
  dist[ofst][ofst] = 0;
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    dist[ofst + x][ofst + y] = -1;
  }
  using P = pair<int, int>;
  queue<P> qu;
  qu.push(P(ofst, ofst));
  while (qu.size()) {
    auto [x, y] = qu.front();
    qu.pop();
    for (int i = 0; i < 6; ++i) {
      int tx = x + dx[i], ty = y + dy[i];
      if (tx < 0 || ty < 0 || tx >= 1000 || ty >= 1000 || dist[tx][ty] == -1 ||
          dist[tx][ty] != inf)
        continue;
      dist[tx][ty] = dist[x][y] + 1;
      qu.push(P(tx, ty));
    }
  }
  if (dist[gx][gy] == inf)
    cout << -1 << endl;
  else
    cout << dist[gx][gy] << endl;
  return 0;
}