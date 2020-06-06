#include <bits/stdc++.h>
using namespace std;

long long n, q;
vector<long long> up, down, tp, res;

int main() {
  cin >> n >> q;
  tp.resize(n);
  up.resize(2 * n);
  down.resize(2 * n);
  for (int i = 0; i < n; ++i) {
    tp[i] = i;
    up[i] = -1;
    up[i + n] = i;
    down[i] = i + n;
    down[i + n] = -1;
  }
  for (int i = 0; i < q; ++i) {
    int f, t, x, nowtp;
    cin >> f >> t >> x;
    --f, --t, --x;
    nowtp = tp[f];
    tp[f] = down[x];
    up[tp[f]] = -1;
    down[x] = tp[t];
    up[down[x]] = x;
    tp[t] = nowtp;
  }
  res.resize(n);
  for (int i = 0; i < n; ++i) {
    int now = up[i + n];
    while (now != -1) {
      res[now] = i + 1;
      now = up[now];
    }
  }
  for (auto p : res) cout << p << endl;
  return 0;
}