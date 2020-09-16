#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  string res;

  cin >> n;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (auto c : s)
      if ('A' <= c && c <= 'Z') res += c;
  }
  cout << res << "UPC" << endl;
  return 0;
}