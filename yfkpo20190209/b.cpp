#include <bits/stdc++.h>
using namespace std;

int k, x, y;
string s = "yfkpo";
char solve();

int main() {
  cin >> k >> y >> x;

  cout << solve() << endl;
  return 0;
}

char solve() {
  int now = k * (y - 1);
  if(y % 2)
    now += x;
  else
    now += k - x + 1;
  return s[(now + 4) % 5];
}