#include <bits/stdc++.h>
using namespace std;

struct dat {
  long long x, h, r;
};

long long n;
vector<dat> v;
vector<long long> c;
vector<long double> sum, num;
map<long long, int> mp;

long double solve();

int main() {
  cin >> n;
  v.resize(n);
  for (auto& p : v) cin >> p.x >> p.h >> p.r;
  cout << fixed << setprecision(10);
  cout << solve() << endl;
  return 0;
}

long double solve() {
  {
    for (int i = 0; i < n; ++i) {
      c.push_back(2 * v[i].x);
      c.push_back(2 * v[i].x - v[i].r);
      c.push_back(2 * v[i].x + v[i].r);
    }
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    int len = c.size();
    for (int i = 0; i < len; ++i) mp[c[i]] = i + 1;
    sum.assign(len + 2, 0);
  }
  for (int i = 0; i < n; ++i) {
    int idl = mp[2 * v[i].x - v[i].r], idm = mp[2 * v[i].x],
        idr = mp[2 * v[i].x + v[i].r];
    long double t = 2.0L * v[i].h / v[i].r;
    sum[idl] += t;
    sum[idm] -= 2 * t;
    sum[idr] += t;
  }
  long double res = 0;
  int len = sum.size();
  for (int i = 1; i < len; ++i) sum[i] += sum[i - 1];
  num.assign(len, 0);
  for (int i = 1; i <= len; ++i) {
    num[i] = sum[i] * (c[i] - c[i - 1]) / 2.0L + num[i - 1];
    res = max(res, num[i]);
  }
  return res;
}