// return (q, l, r): n / i == q(l <= i < r)
template <class T>
vector<tuple<T, T, T>> quotient_range(T n) {
  vector<tuple<T, T, T>> res;
  T l = T(1);
  while (l <= n) {
    T r = n / (n / l) + 1;
    res.emplace_back(n / l, l, r);
    l = r;
  }
  return res;
}