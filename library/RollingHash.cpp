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
    for (int i = 1; i <= len; ++i) pow[i] = (long long)pow[i - 1] * Base % Mod;
  }
  void add(const string &s) {
    int id = hash.size();
    hash.push_back(vector<int>((int)s.size() + 1, 0));
    sethash(id, s);
  }
  void changestr(const int &id, const string &s) {
    assert(id < (int)hash.size());
    sethash(id, s);
  }
  void sethash(const int &id, const string &s) {
    int len = s.size();
    for (int i = 0; i < len; ++i) {
      hash[id][i + 1] = (long long)hash[id][i] * Base % Mod;
      hash[id][i + 1] += s[i];
      if (hash[id][i + 1] >= Mod) hash[id][i + 1] -= Mod;
    }
  }
  // [l,r),0-indexed
  long long calchash(const int &id, const int &l, const int &r) const {
    assert(r >= l);
    long long res = hash[id][r];
    res -= (long long)hash[id][l] * pow[r - l] % Mod;
    if (res < 0) res += Mod;
    if (res >= Mod) res -= Mod;
    return res;
  }
  inline bool issame(const int &idl, const int &ll, const int &lr,
                     const int &idr, const int &rl, const int &rr) const {
    return calchash(idl, ll, lr) == calchash(idr, rl, rr);
  }
};
