template <class T>
struct Suffix_Array {
  T s;
  int ssize, nowlen;
  vector<int> rank, tmp, sa, lcp;
  Suffix_Array() {}
  Suffix_Array(T news, bool reqlcp = 0) {
    s = news;
    ssize = s.size();
    nowlen = 0;
    rank.resize(ssize + 1);
    tmp.resize(ssize + 1);
    sa.resize(ssize + 1);
    constuct_sa();
    if (reqlcp) constuct_lcp();
  }

  void constuct_sa() {
    auto cmp = [&](int l, int r) {
      if (rank[l] != rank[r]) return rank[l] < rank[r];
      int rx = l + nowlen <= ssize ? rank[l + nowlen] : -1;
      int ly = r + nowlen <= ssize ? rank[r + nowlen] : -1;
      return rx < ly;
    };

    for (int i = 0; i <= ssize; ++i) {
      sa[i] = i;
      rank[i] = i < ssize ? s[i] : -1;
    }
    for (nowlen = 1; nowlen <= ssize; nowlen *= 2) {
      sort(sa.begin(), sa.end(), cmp);
      tmp[sa[0]] = 0;
      for (int i = 1; i <= ssize; ++i)
        tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
      for (int i = 0; i <= ssize; ++i) rank[i] = tmp[i];
    }
  }
  // Longest Common Prefix Array
  void constuct_lcp() {
    lcp.resize(ssize + 1);
    for (int i = 0; i <= ssize; ++i) rank[sa[i]] = i;
    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < ssize; ++i) {
      int j = sa[rank[i] - 1];
      if (h > 0) --h;
      for (; j + h < ssize && i + h < ssize; ++h)
        if (s[j + h] != s[i + h]) break;
      lcp[rank[i] - 1] = h;
    }
  }

  bool contain(T& nowt) {
    int lef = 0, righ = strlen, tsize = nowt.size();
    while (righ - lef > 1) {
      int mid = (lef + righ) / 2;
      if (s.compare(sa[mid], tsize, nowt) < 0)
        lef = mid;
      else
        righ = mid;
    }
    return s.compare(sa[righ], tsize, nowt) == 0;
  }
};