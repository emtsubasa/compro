#include <bits/stdc++.h>
using namespace std;

long long n;
vector<string> s, t = {".###..#..###.###.#.#.###.###.###.###.###.",
                       ".#.#.##....#...#.#.#.#...#.....#.#.#.#.#.",
                       ".#.#..#..###.###.###.###.###...#.###.###.",
                       ".#.#..#..#.....#...#...#.#.#...#.#.#...#.",
                       ".###.###.###.###...#.###.###...#.###.###."};
string solve();

int main() {
  cin >> n;
  s.resize(5);
  for (int i = 0; i < 5; ++i) cin >> s[i];
  cout << solve() << endl;
  return 0;
}

string solve() {
  string res;
  for (int i = 0; i < n; ++i) {
    int st = 4 * i;
    for (int j = 0; j < 10; ++j) {
      bool ch = 1;
      for (int k = 0; k < 5; ++k) {
        if (s[k].substr(st, 4) != t[k].substr(4 * j, 4)) ch = 0;
      }
      if (ch) res += j + '0';
    }
  }
  return res;
}