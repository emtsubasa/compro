#include <bits/stdc++.h>
using namespace std;

long long q, m;
vector<string> s;
vector<long long> th(1, 1), memo;

string solve();
void dfs(const long long now);
long long dec(string& st) {
  long long res = 0;
  for (int i = 0; i < m; ++i) res += (st[i] - '0') * th[i];
  return res;
}
string enc(long long x) {
  string res;
  for (int i = 0; i < m; ++i) {
    res += '0' + x % 3;
    x /= 3;
  }
  return res;
}

int main() {
  cin >> q >> m;
  for (int i = 0; i < m; ++i) {
    long long now = th.back();
    th.push_back(now * 3);
  }
  memo.assign(th.back(), 0);
  s.resize(q);
  for (int i = 0; i < q; ++i) {
    cin >> s[i];
    for (auto& c : s[i]) --c;
  }
  cout << solve() << endl;
  return 0;
}

string solve() {
  string res;
  for (int i = 0; i < q; ++i) {
    long long now = dec(s[i]);
    int p = memo[now];
    res += '0' + (p == 2);
    if (!p) {
      dfs(now);
      memo[now] = 1;
    }
  }
  return res;
}

void dfs(const long long now) {
  for (int i = 0; i < m; ++i)
    if (now / th[i] % 3 != 0) {
      long long nxt = now - th[i];
      if (memo[nxt] != 2) {
        memo[nxt] = 2;
        dfs(nxt);
      }
    }
}