struct NTT_ModInt {
  int base, maxb, mod;
  mint root;
  vector<int> rv;
  vector<mint> roots, invr;
  NTT_ModInt()
      : base(1),
        mod(mint().get_mod()),
        rv({0, 1}),
        roots({0, 1}),
        invr({0, 1}) {
    int tmp = mod - 1;
    maxb = 0;
    while (!(tmp & 1)) tmp >>= 1, ++maxb;
    root = 2;
    while (root.pow((mod - 1) >> 1) == 1) root += 1;
    assert(root.pow(mod - 1) == 1);
    root = root.pow((mod - 1) >> maxb);
  }

  void ensure_base(int nb) {
    if (nb <= base) return;
    rv.resize(1 << nb);
    roots.resize(1 << nb);
    invr.resize(1 << nb);
    for (int i = 0; i < (1 << nb); ++i)
      rv[i] = (rv[i >> 1] >> 1) + ((i & 1) << (nb - 1));
    assert(nb <= maxb);
    while (base < nb) {
      mint z = root.pow(1 << (maxb - 1 - base)), invz = z.inverse();
      for (int i = 1 << (base - 1); i < (1 << base); ++i) {
        roots[i << 1] = roots[i];
        roots[(i << 1) + 1] = roots[i] * z;
        invr[i << 1] = invr[i];
        invr[(i << 1) + 1] = invr[i] * invz;
      }
      ++base;
    }
  }
  void ntt(vector<mint> &a, int n, bool sg = 0) {
    assert((n & (n - 1)) == 0);
    int dif = base - __builtin_ctz(n);
    for (int i = 0; i < n; ++i)
      if (i < (rv[i] >> dif)) swap(a[i], a[rv[i] >> dif]);
    for (int k = 1; k < n; k <<= 1)
      for (int i = 0; i < n; i += 2 * k)
        for (int j = 0; j < k; ++j) {
          mint z = a[i + j + k] * (sg ? roots[j + k] : invr[j + k]);
          a[i + j + k] = a[i + j] - z;
          a[i + j] += z;
        }
    mint invn = mint(n).inverse();
    if (sg)
      for (int i = 0; i < n; ++i) a[i] *= invn;
  }
  vector<mint> multiply(vector<mint> a, vector<mint> b) {
    int need = a.size() + b.size() - 1;
    int nb = 1;
    while ((1 << nb) < need) ++nb;
    ensure_base(nb);
    int sz = 1 << nb;
    a.resize(sz);
    b.resize(sz);
    ntt(a, sz);
    ntt(b, sz);
    for (int i = 0; i < sz; ++i) a[i] *= b[i];
    ntt(a, sz, 1);
    a.resize(need);
    return a;
  }
};