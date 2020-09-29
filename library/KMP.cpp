// A[i]: S[0,i-1] longest match(pre and suf)
template <class T>
struct KMP {
  vector<int> A;
  int n;
  T s;
  KMP() {}
  KMP(T _s) {
    s = _s;
    n = s.size();
    A.assign(n + 1, -1);
    for (int i = 0, j = -1; i < n; ++i) {
      while (j >= 0 && s[i] != s[j]) j = A[j];
      ++j;
      /* KMP
      if(i + 1 < n && s[i + 1] == s[j])
        A[i + 1] = A[j];
      else
        //*/
      A[i + 1] = j;
    }
  }
  inline const int &operator[](int k) const { return (A[k]); }
  vector<int> calccycle() {
    vector<int> res(n, 0);
    for (int i = 0; i < n; ++i) res[i] = i + 1 - A[i + 1];
    return res;
  }
  // search s in t
  vector<int> search(const T &t) {
    vector<int> res;
    int tsize = t.size();
    for (int i = 0, j = 0; i + j < tsize;) {
      if (s[j] == t[i + j]) {
        if (++j != n) continue;
        res.push_back(i);
      }
      i += j - A[j];
      j = max(A[j], 0);
    }
    return res;
  }
};