template <class T>
T largest_rectangle(const vector<T>& v) {
  T res = 0;
  int n = v.size();
  vector<T> h, id;
  h.push_back(0);
  for (int i = 0; i <= n; ++i) {
    int nxt = i;
    T now = i == n ? 0 : v[i];
    while (now < h.back()) {
      nxt = id.back();
      res = max(res, h.back() * (i - nxt));
      h.pop_back();
      id.pop_back();
    }
    if (now > h.back()) {
      h.push_back(now);
      id.push_back(nxt);
    }
  }
  return res;
}