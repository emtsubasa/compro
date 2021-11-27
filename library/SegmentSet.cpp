// [l,r]
template <class T, T inf = numeric_limits<T>::max()>
struct SegmentSet {
  using Pt = pair<T, T>;
  set<Pt> st;
  SegmentSet() {
    st.clear();
    st.emplace(-inf, -inf);
    st.emplace(inf, inf);
  }

  bool covered(T l, T r) {
    auto [x, y] = *prev(st.upper_bound(Pt(l, inf)));
    return x <= l && r <= y;
  }
  bool exist(T x) { return covered(x, x); }

  T insert(int l, int r) {
    auto it = prev(st.upper_bound(Pt(l, inf)));
    // cover
    if (it->first <= l && r <= it->second) return T(0);
    T er = T(0);
    if (l - 1 <= it->second) {
      l = it->first;
      er += it->second - it->first + 1;
      it = st.erase(it);
    } else
      it = next(it);
    while (it->first <= r + 1) {
      r = max(r, it->second);
      er += it->second - it->first + 1;
      it = st.erase(it);
    }
    st.emplace(l, r);
    return r - l + 1 - er;
  }
  T insert(int x) { return insert(x, x); }

  T erase(int l, int r) {
    auto it = prev(st.upper_bound(Pt(l, inf)));
    // cover
    if (it->first <= l && r <= it->second) {
      if (it->first < l) st.emplace(it->first, l - 1);
      if (r < it->second) st.emplace(r + 1, it->second);
      st.erase(it);
      return r - l + 1;
    }
    T res = T(0);
    if (l <= it->second) {
      res += it->second - l + 1;
      if (it->first < l) st.emplace(it->first, l - 1);
      it = st.erase(it);
    } else
      it = next(it);
    while (it->first <= r) {
      res += min(r, it->second) - it->first + 1;
      if (r < it->second) st.emplace(r + 1, it->second);
      it = st.erase(it);
    }
    return res;
  }
  T erase(int x) { return erase(x, x); }

  // [x,inf)
  T mex(T x = T(0)) {
    auto [l, r] = *prev(st.upper_bound(Pt(x, inf)));
    // cover
    if (x <= r) return r + 1;
    return x;
  }

  friend ostream &operator<<(ostream &os, SegmentSet &p) {
    for (auto &[l, r] : p.st)
      if (abs(l) != inf) os << "[" << l << ", " << r << "] ";
    return (os);
  }
};
