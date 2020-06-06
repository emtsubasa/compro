#include <bits/stdc++.h>
using namespace std;

long long n;
vector<string> a;
vector<vector<bool>> ch;

int main() {
  cin >> n;
  a.resize(n);
  ch.assign(n, vector<bool>(26, 0));
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    for (int j = 0; j < n; ++j) ch[i][a[i][j] - 'a'] = 1;
  }
  string res;
  for (int i = 0; i < n; ++i) {
    bool flg = 0;
    for (int j = 0; j < 26; ++j)
      if (ch[i][j] && ch[n - 1 - i][j]) {
        res += 'a' + j;
        flg = 1;
        break;
      }
    if (!flg) {
      cout << -1 << endl;
      return 0;
    }
  }
  cout << res << endl;
  return 0;
}