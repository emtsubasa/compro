#include <bits/stdc++.h>
using namespace std;

string s, t;

int main() {
  cin >> s >> t;
  if (s == t)
    cout << "same" << endl;
  else {
    for (auto &cha : s) cha = toupper(cha);
    for (auto &cha : t) cha = toupper(cha);
    bool ch = s == t;
    if (ch)
      cout << "case-insensitive" << endl;
    else
      cout << "different" << endl;
  }

  cout << endl;
  return 0;
}