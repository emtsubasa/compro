#include <bits/stdc++.h>
using namespace std;

using P = pair<int, char>;
int n;
string s;
vector<int> cnt(26, 0);
priority_queue<P> pq;

int main() {
  cin >> n >> s;
  for (auto c : s) ++cnt[c - 'a'];
  for (int i = 0; i < 26; ++i)
    if (cnt[i]) pq.push(P(cnt[i], 'a' + i));
  P bf1(0, '-'), bf2(0, '-'), bf3(0, '-');
  string res;
  for (int i = 0; i < n; ++i) {
    if (bf1.first) pq.push(bf1);
    if (!pq.size()) {
      cout << -1 << endl;
      return 0;
    }
    bf1 = bf2;
    bf2 = bf3;
    bf3 = pq.top();
    pq.pop();
    res += bf3.second;
    --bf3.first;
  }
  cout << res << endl;
  return 0;
}