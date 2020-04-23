#include <bits/stdc++.h>
using namespace std;

long long res = 0, bit = 0;
long long point[] = {18, 16, 19, 12, 15, 17, 18, 20, 15, 24, 25, 22,
                     18, 13, 20, 14, 17, 19, 13, 17, 18, 15, 22};
map<string, int> mp;
set<string> st;
vector<bool> dp(1LL << 23, 0);
vector<string> s;
vector<vector<bool>> memo(23, vector<bool>(23, 0));
vector<vector<string>> t;

int main() {
  s.resize(23);
  t.resize(23);
  for (int i = 0; i < 23; ++i) {
    cin >> s[i];
    mp[s[i]] = i;
    int p;
    cin >> p;
    t[i].resize(p);
    st.insert(s[i]);
    for (int j = 0; j < p; ++j) {
      cin >> t[i][j];
      if (j != p - 1) t[i][j].pop_back();
      st.insert(t[i][j]);
    }
  }
  for (int i = 0; i < 23; ++i)
    for (auto x : t[i]) memo[mp[s[i]]][mp[x]] = 1;

  dp[0] = 1;
  for (int i = 1; i < (1LL << 23); ++i) {
    bool ch = 1;
    int now = -1;
    for (int j = 22; j >= 0; --j)
      if (i >> j & 1) {
        now = j;
        break;
      }
    if (!dp[i - (1 << now)]) continue;
    for (int j = 0; j < 23; ++j)
      if ((i >> j & 1) && j != now && memo[j][now]) ch = 0;
    if (ch) {
      dp[i] = 1;
      long long sum = 0;
      for (int j = 0; j < 23; ++j)
        if (i >> j & 1) sum += point[j];
      if (res < sum) {
        res = sum;
        bit = i;
      }
    }
  }
  vector<string> v;
  for (int i = 0; i < 23; ++i)
    if (bit >> i & 1) v.push_back(s[i]);

  sort(v.begin(), v.end());
  cout << res << endl;
  for (auto x : v) cout << x << endl;
  return 0;
}