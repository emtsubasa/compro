// use z_algorithm
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