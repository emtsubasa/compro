// 0-indexed
template <class T>
struct Fib {
  int n, l, r, len;
  vector<long long> fib, lens;
  Fib(int _n = 1000000) : n(_n), fib({1, 1}), lens({1, 2}) {
    while (lens.back() < n) {
      int len = fib.size();
      fib.push_back(fib[len - 2] + fib[len - 1]);
      lens.push_back(lens.back() + fib.back());
    }
  }
  void reset() { l = -1, r = lens.back(), len = fib.size(); }

  template <typename F, typename G>
  T calc(F& query, G& check, T unit) {
    reset();
    vector<int> called(r, 0);
    vector<T> memo(r, unit);
    for (int i = len - 1; i >= 0; --i) {
      int ml = l + fib[i], mr = r - fib[i];
      if (!called[ml] && ml < n) memo[ml] = query(ml), called[ml] = 1;
      if (!called[mr] && mr < n) memo[mr] = query(mr), called[mr] = 1;
      if (check(memo[ml], memo[mr]))
        l = ml;
      else
        r = mr;
    }
    return memo[r];
  }
};