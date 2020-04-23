#include <bits/stdc++.h>
using namespace std;

struct dat {
  long long r;
  string s;
  bool operator<(const dat &d) const { return r > d.r; }
};

long long n;
vector<dat> v;

int main() {
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; ++i) cin >> v[i].s >> v[i].r;
  sort(v.begin(), v.end());
  long long cnt = 0, r = v[0].r;
  for (int i = 0; i < n && v[i].r == r; ++i) {
    if (v[i].s == "True")
      ++cnt;
    else
      --cnt;
  }
  if (cnt > 0)
    cout << "True" << endl;
  else if (cnt < 0)
    cout << "False" << endl;
  else
    cout << "Draw" << endl;
  return 0;
}