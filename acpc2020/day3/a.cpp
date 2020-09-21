#include <bits/stdc++.h>
using namespace std;

int h, w;
int sig[] = {-1, 0, 1, 0};
int wall[] = {0, 0, 1, 1};
string d, dir = "NWSE";
vector<string> s;

int main() {
  cin >> h >> w;
  wall[0] = h, wall[1] = w;
  s.resize(h);
  for (auto& p : s) cin >> p;
  cin >> d;
  int res = 0;
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      if (s[i][j] == '#') {
        int now = max(h, w);
        for (int k = 0; k < 4; ++k)
          for (auto c : d)
            if (dir[k] == c)
              now = min(now, wall[k] + sig[k] * i + sig[1 ^ k] * j);
        res = max(res, now);
      }
  cout << res << endl;
  return 0;
}