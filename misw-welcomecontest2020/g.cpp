#include <bits/stdc++.h>
using namespace std;

struct dat {
  long long l, r;
  bool ismis;
  bool operator<(const dat &d) const {
    if (r != d.r) return r < d.r;
    if (l != d.l) return l < d.l;
    return ismis;
  }
};

long long n, m;
vector<int> sum;
vector<dat> v, clas, mis;

bool solve();

int main() {
  cin >> n >> m;
  sum.assign(12000, 0);
  for (int i = 0; i < n; ++i) {
    long long nowl = 0, nowr = 0, w, h, mi;
    cin >> w >> h >> mi;
    nowl = 1440 * w + 60 * h + mi;
    cin >> h >> mi;
    nowr = nowl + 60 * h + mi;
    ++sum[nowl];
    --sum[nowr + 1];
    v.push_back({nowl, nowr, 1});
    mis.push_back({nowl, nowr, 1});
  }
  for (int i = 1; i < sum.size(); ++i) sum[i] += sum[i - 1];
  for (int i = 0; i < m; ++i) {
    long long nowl = 0, nowr = 0, w, h, mi;
    cin >> w >> h >> mi;
    nowl = 1440 * w + 60 * h + mi;
    cin >> h >> mi;
    nowr = nowl + 60 * h + mi;
    v.push_back({nowl, nowr, 0});
    clas.push_back({nowl, nowr, 0});
  }
  sort(clas.begin(), clas.end());
  sort(mis.begin(), mis.end());
  sort(v.begin(), v.end());
  if (solve())
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
  return 0;
}

bool solve() {
  int cnt = 0, now = 0;
  for (int i = 0; i < n; ++i)
    if (now <= mis[i].l) {
      now = mis[i].r;
      ++cnt;
    }
  if (cnt != n) return 0;
  cnt = now = 0;
  for (int i = 0; i < n + m; ++i)
    if (now <= v[i].l) {
      now = v[i].r;
      ++cnt;
    }
  now = 0;
  cnt -= n;
  n += 2;
  mis.push_back({0LL, 0LL, 1});
  mis.push_back({(long long)1e8, (long long)1e8, 1});
  sort(mis.begin(), mis.end());
  for (int i = 1, j = 0; i < n && j < m; ++i) {
    now = mis[i - 1].r;
    while (j < m && now > clas[j].l) ++j;
    while (j < m && clas[j].r <= mis[i].l) {
      if (now <= clas[j].l) {
        now = clas[j].r;
        --cnt;
      }
      ++j;
    }
  }
  return cnt == 0;
}