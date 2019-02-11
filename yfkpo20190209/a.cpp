#include <bits/stdc++.h>
using namespace std;

string s[2];

string solve();

int main() {
  cin >> s[0] >> s[1];

  cout << solve() << endl;
  return 0;
}

string solve() {
  string ans;
  int now = 0;
  for(int i = 0; i < 2; ++i)
    reverse(s[i].begin(), s[i].end());
  for(int i = 0; i < max(s[0].size(), s[1].size()); ++i) {
    if(i < s[0].size() && s[0][i] == 'B') ++now;
    if(i < s[1].size() && s[1][i] == 'B') ++now;
    if(now % 2 == 1)
      ans += 'B';
    else
      ans += 'b';
    now /= 2;
  }
  if(now == 1) ans += 'B';
  reverse(ans.begin(), ans.end());
  return ans;
}