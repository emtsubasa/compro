struct RollingHash {
  int Mod, Base;
  vector<int> pow;
  vector<vector<int>> hash;
  // mod : 1e9 + 9,base : 1007
  RollingHash(const int len = 3000000, const int mod = (int)(1e9 + 7),
              const int base = 1009) {
    Mod = mod;
    Base = base;
    pow.assign(len + 1, 0);
    pow[0] = 1;
    for (int i = 1; i <= len; ++i) pow[i] = 1LL * pow[i - 1] * Base % Mod;
  }
  template <class T>
  int add(const T &s) {
    int id = hash.size();
    hash.push_back(vector<int>());
    sethash(id, s);
    return id;
  }
  template <class T>
  void sethash(const int id, const T &s) {
    assert(id < (int)hash.size());
    int len = s.size();
    hash[id].resize(len + 1, 0);
    for (int i = 0; i < len; ++i) {
      hash[id][i + 1] = 1LL * hash[id][i] * Base % Mod;
      if ((hash[id][i + 1] += s[i] + 1) >= Mod) hash[id][i + 1] -= Mod;
    }
  }
  // [l,r),0-indexed
  inline int calchash(const int &id, const int &l, const int &r) const {
    assert(r >= l);
    int res = hash[id][r];
    res += Mod - 1LL * hash[id][l] * pow[r - l] % Mod;
    if (res >= Mod) res -= Mod;
    return res;
  }
  inline bool issame(const int &idl, const int &ll, const int &lr,
                     const int &idr, const int &rl, const int &rr) const {
    return calchash(idl, ll, lr) == calchash(idr, rl, rr);
  }
};