#include <bits/stdc++.h>
using namespace std;

long long a, r, n;

int main() {
  cin >> a >> r >> n;
  if (r == 1) {
    if (a > (long long)(1e9))
      cout << "large" << endl;
    else
      cout << a << endl;
  } else {
    for (int i = 0; i < n - 1; ++i) {
      a *= r;
      if (a > (long long)(1e9)) {
        cout << "large" << endl;
        return 0;
      }
    }
    cout << a << endl;
  }

  return 0;
}