// 0-indexed
struct SuccinctIndexableDictionary {
  using ui = unsigned int;
  int len, blen;
  vector<ui> bit, sum;
  SuccinctIndexableDictionary(int _len = 0)
      : len(_len), blen((_len + 63) >> 5) {
    bit.assign(blen, 0), sum.assign(blen, 0);
  }
  SuccinctIndexableDictionary(const vector<int> &v) {
    len = v.size(), blen = ((len + 63) >> 5);
    bit.assign(blen, 0), sum.assign(blen, 0);
    for (int i = 0; i < len; ++i)
      if (v[i]) set(i);
    build();
  }
  // v[k] = 1
  void set(int k) { bit[k >> 5] |= 1U << (k & 31); }
  inline int popcount(ui x) { return __builtin_popcount(x); }
  void build() {
    sum[0] = 0U;
    for (int i = 1; i < blen; ++i) sum[i] = sum[i - 1] + popcount(bit[i - 1]);
  }
  int rank(int k) {
    return (sum[k >> 5] + popcount(bit[k >> 5] & ((1U << (k & 31)) - 1)));
  }
  // count b in [0,k)
  int rank(int b, int k) { return (b ? rank(k) : k - rank(k)); }
  // search k-th b (0-indexed)
  int select(int b, int k) {
    if (rank(b, len - 1) < k) return -1;
    int l = -1, r = len - 1;
    while (r - l > 1) {
      int mid = (l + r) >> 1;
      if (rank(b, mid) >= k)
        r = mid;
      else
        l = mid;
    }
    return l;
  }
  // v[k]
  bool operator[](int k) { return ((bit[k >> 5] >> (k & 31)) & 1); }
};

template <class T, int high = 31>
struct WaveletMatrix {
  int len;
  vector<SuccinctIndexableDictionary> mat;
  vector<int> mid;
  WaveletMatrix() {}
  WaveletMatrix(vector<T> v) : len(v.size()) {
    vector<T> lv(len), rv(len);
    mat.assign(high, SuccinctIndexableDictionary(len));
    mid.resize(high);
    for (int t = high - 1; t >= 0; --t) {
      int l = 0, r = 0;
      for (int i = 0; i < len; ++i)
        if (v[i] >> t & 1)
          mat[t].set(i), rv[r++] = v[i];
        else
          lv[l++] = v[i];
      mid[t] = l, mat[t].build(), v.swap(lv);
      for (int i = 0; i < r; ++i) v[l + i] = rv[i];
    }
  }
  // v[k]
  T access(int k) {
    T res = 0;
    for (int t = high - 1; t >= 0; --t) {
      bool b = mat[t][k];
      if (b) res |= T(1) << t;
      k = mat[t].rank(b, k) + mid[t] * b;
    }
    return res;
  }
  T operator[](const int &k) { return access(k); }

  pair<int, int> succ(bool b, int l, int r, int t) {
    return pair<int, int>(mat[t].rank(b, l) + mid[t] * b,
                          mat[t].rank(b, r) + mid[t] * b);
  }

  // count x in [0,r)
  int rank(const T &x, int r) {
    int l = 0;
    for (int t = high - 1; t >= 0; --t) tie(l, r) = succ(x >> t & 1, l, r, t);
    return r - l;
  }
  //   WIP  search k-th x (0-indexed)
  int select(const T &x, int k) {}
  // k-th(0-indexed) smallest number in [l,r)
  T kth_smallest(int l, int r, int k) {
    assert(0 <= k && k < r - l);
    T res = 0;
    for (int t = high - 1; t >= 0; --t) {
      int cnt = mat[t].rank(0, r) - mat[t].rank(0, l);
      bool ch = cnt <= k;
      if (ch) res |= T(1) << t, k -= cnt;
      tie(l, r) = succ(ch, l, r, t);
    }
    return res;
  }
  // k-th(0-indexed) largest number in [l,r)
  T kth_largest(int l, int r, int k) {
    return kth_smallest(l, r, r - l - k - 1);
  }
  // count x < u in [l,r)
  int range_freq(int l, int r, int u) {
    int res = 0;
    for (int t = high - 1; t >= 0; --t) {
      bool b = u >> t & 1;
      if (b) res += mat[t].rank(0, r) - mat[t].rank(0, l);
      tie(l, r) = succ(b, l, r, t);
    }
    return res;
  }
  // count d <= x < u in [l,r)
  int range_freq(int l, int r, int d, int u) {
    return range_freq(l, r, u) - range_freq(l, r, d);
  }
  // max y < x in[l,r)
  T prev_value(int l, int r, T x) {
    int cnt = range_freq(l, r, x);
    return !cnt ? T(-1) : kth_smallest(l, r, cnt - 1);
  }
  // min y >= x in [l,r)
  T next_value(int l, int r, T x) {
    int cnt = range_freq(l, r, x);
    return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);
  }
};