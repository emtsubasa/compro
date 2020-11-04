// w:weight,v:value,m:limit, maximize v
template <class T>
vector<T> knapsack_with_limitations(const int lim, const vector<T> &w,
                                    const vector<T> &m, const vector<T> &v,
                                    const T inf = -1) {
  int n = w.size();
  assert(n == m.size() && n == v.size());
  vector<T> dp(lim + 1, inf), deqv(lim + 1);
  vector<int> deq(lim + 1);
  dp[0] = 0;
  for (int i = 0; i < n; ++i)
    for (int a = 0; a < w[i]; ++a) {
      int s = 0, t = 0;
      for (int j = 0; w[i] * j + a <= lim; ++j) {
        if (dp[w[i] * j + a] != inf) {
          auto val = dp[w[i] * j + a] - j * v[i];
          while (s < t && val > deqv[t - 1]) --t;
          deq[t] = j;
          deqv[t++] = val;
        }
        if (s < t) {
          dp[j * w[i] + a] = deqv[s] + j * v[i];
          if (deq[s] == j - m[i]) ++s;
        }
      }
    }
  return dp;
}