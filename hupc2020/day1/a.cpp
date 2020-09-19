#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
  int now = 0;
  cin >> n;
  {
    int a, t;
    cin >> a >> t;
    if (!t) a = a * 1.1;
    now = a;
  }
  vector<int> res;
  for (int i = 1; i < n; ++i) {
    int a, t;
    cin >> a >> t;
    if (!t) a = a * 1.1;
    if (now > a) res.push_back(i + 1);
  }
  if (res.size()) {
    cout << "Yes" << endl;
    for (auto p : res) cout << p << endl;
  } else
    cout << "No" << endl;
  return 0;
}