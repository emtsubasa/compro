#include "bits/stdc++.h"
using namespace std;

int main() {
  int n;
  string s, t;
  cin >> n >> s >> t;
  {
    set<char> sts, stt;
    for (char c : s) sts.insert(c);
    for (char c : t) stt.insert(c);
    if (sts.size() == 1 || stt.size() == 1) {
      if (sts.size() == 1 && stt.size() == 1) {
        char s1 = *sts.begin();
        char s2 = *stt.begin();
        cout << (s1 == s2 ? "Yes" : "No") << endl;
      } else {
        cout << "No" << endl;
      }
      return 0;
    }
  }
  map<int, int> mp;
  mp['R'] = 0;
  mp['G'] = 1;
  mp['B'] = 2;
  mp['Y'] = 3;
  int res = 0;
  for (auto c : s) res ^= mp[c];
  for (auto c : t) res ^= mp[c];
  if (!res)
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
  return 0;
}