#include <bits/stdc++.h>
using namespace std;

long long n, q;
vector<long long> rc[2];
bool ch = 0;

int main() {
  cin >> n >> q;
  rc[0].assign(n, 0);
  rc[1].assign(n, 0);
  for (int i = 0; i < n; ++i) rc[0][i] = rc[1][i] = i;
  for (int i = 0; i < q; ++i) {
    int b, x, y;
    cin >> b;
    if (b == 1) {
      cin >> x >> y;
      swap(rc[ch][--x], rc[ch][--y]);
    } else if (b == 2) {
      cin >> x >> y;
      swap(rc[!ch][--x], rc[!ch][--y]);
    } else if (b == 3)
      ch = !ch;
    else {
      cin >> x >> y;
      if (!ch)
        cout << rc[0][--x] * n + rc[1][--y] << endl;
      else
        cout << rc[1][--x] + rc[0][--y] * n << endl;
    }
  }
  return 0;
}