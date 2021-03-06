#include <bits/stdc++.h>
using namespace std;

template <class T>
vector<int> z_algorithm(const T& s) {
  vector<int> res;
  int i = 1, j = 0, ssize = s.size();
  res.resize(s.size());
  res[0] = ssize;
  while (i < ssize) {
    while (i + j < ssize && s[j] == s[i + j]) ++j;
    res[i] = j;
    if (j == 0) {
      ++i;
      continue;
    }
    int k = 1;
    while (i + k < ssize && k + res[k] < j) res[i + k] = res[k], ++k;
    i += k, j -= k;
  }
  return res;
}

template <class T>
void run_enumerate(int l, int r, const T& s,
                   vector<vector<pair<int, int>>>& res) {
  if (r - l <= 1) return;
  int m = (l + r) >> 1;
  run_enumerate(l, m, s, res);
  run_enumerate(m, r, s, res);

  auto func = [&](bool rev = 0) {
    T t, tl, tr;
    copy(s.begin() + l, s.begin() + r, back_inserter(t));
    if (rev) {
      reverse(t.begin(), t.end());
      m = l + r - m;
    }
    int len = r - l, mlen = m - l;
    copy(t.begin(), t.begin() + mlen, back_inserter(tl));
    reverse(tl.begin(), tl.end());
    copy(t.begin() + mlen, t.end(), back_inserter(tr));
    copy(t.begin(), t.end(), back_inserter(tr));
    auto zl = z_algorithm(tl), zr = z_algorithm(tr);
    zl.push_back(0);
    for (int k = 1; k <= mlen; ++k) {
      int li = m - k - zl[k], ri = m + min(r - m, zr[len - k]);
      if (rev) {
        swap(li, ri);
        li = l + r - li;
        ri = l + r - ri;
      }
      if (ri - li < 2 * k) continue;
      if (li > 0 && s[li - 1] == s[li - 1 + k]) continue;
      if (ri < s.size() && s[ri] == s[ri - k]) continue;
      res[li].emplace_back(ri, k);
    }
  };
  func();
  func(1);
}

template <class T>
vector<vector<pair<int, int>>> run_enumerate(const T& s) {
  int len = s.size();
  vector<vector<pair<int, int>>> run(len), res(len);
  run_enumerate(0, len, s, run);
  for (int i = 0; i < len; ++i) {
    int rlen = run[i].size();
    sort(run[i].begin(), run[i].end());
    for (int j = 0; j < rlen; ++j)
      if (j == 0 || run[i][j].first != run[i][j - 1].first)
        res[i].push_back(run[i][j]);
  }
  return res;
}

long long n;
vector<int> s;

long long solve();

int main() {
  cin >> n;
  s.resize(n);
  for (auto& p : s) cin >> p;
  cout << solve() << endl;
  return 0;
}

long long solve() {
  long long res = n * (n + 1) / 2;
  auto run = run_enumerate(s);
  for (int i = 0; i < n; ++i)
    for (auto [r, t] : run[i]) {
      long long len = r - i, d = len / t;
      res += (d - 1) * d * (3 * (len + 1) - 2 * (d + 1) * t) / 6;
    }
  return res;
}