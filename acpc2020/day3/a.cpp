#include <bits/stdc++.h>
using namespace std;

int h, w;
string d;
vector<string> s;

int main() {
  cin >> h >> w;
  s.resize(h);
  for (auto& p : s) cin >> p;
  cin >> d;
  int res = 0, x = 0, y = 0;
  for (auto c : d)
    if (c == 'N')
      x += 1;
    else if (c == 'S')
      x -= 1;
    else if (c == 'W')
      y += 1;
    else
      y -= 1;
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      if (s[i][j] == '#') {
        int now = max(h, w);
        if (x > 0)
          now = min(now, h - i);
        else if (x < 0)
          now = min(now, i + 1);
        if (y > 0)
          now = min(now, w - j);
        else if (y < 0)
          now = min(now, j + 1);
        res = max(res, now);
      }
  cout << res << endl;
  return 0;
}