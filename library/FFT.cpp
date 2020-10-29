// max(res[i]) <= 2^53 -> no error
struct FFT {
  struct CP {
    double x, y;

    CP() : x(0), y(0) {}

    CP(double x, double y) : x(x), y(y) {}

    inline CP operator+(const CP &c) const { return CP(x + c.x, y + c.y); }

    inline CP operator-(const CP &c) const { return CP(x - c.x, y - c.y); }

    inline CP operator*(const CP &c) const {
      return CP(x * c.x - y * c.y, x * c.y + y * c.x);
    }
    CP &operator*=(const CP &p) {
      *this = CP(*this) * p;
      return *this;
    }
    CP &operator/=(const double &p) {
      x /= p, y /= p;
      return *this;
    }

    inline CP conj() const { return CP(x, -y); }
  };
  const double PI = acos(-1);
  int base = 1;
  vector<CP> roots{CP(0, 0), CP(1, 0)};
  vector<int> rv{0, 1};
  FFT() {}
  void ensure_base(int nb) {
    if (nb <= base) return;
    rv.resize(1 << nb);
    roots.resize(1 << nb);
    for (int i = 0; i < (1 << nb); ++i)
      rv[i] = (rv[i >> 1] >> 1) + ((i & 1) << (nb - 1));
    while (base < nb) {
      double arg = PI * 2.0 / (1 << (base + 1));
      for (int i = 1 << (base - 1); i < (1 << base); ++i) {
        roots[i << 1] = roots[i];
        double narg = arg * (2 * i + 1 - (1 << base));
        roots[(i << 1) + 1] = CP(cos(narg), sin(narg));
      }
      ++base;
    }
  }
  void fft(vector<CP> &a, int n, bool sg = 0) {
    assert((n & (n - 1)) == 0);
    int dif = base - __builtin_ctz(n);
    for (int i = 0; i < n; ++i)
      if (i < (rv[i] >> dif)) swap(a[i], a[rv[i] >> dif]);
    for (int k = 1; k < n; k <<= 1)
      for (int i = 0; i < n; i += 2 * k)
        for (int j = 0; j < k; ++j) {
          CP z = a[i + j + k] * (sg ? roots[j + k] : roots[j + k].conj());
          a[i + j + k] = a[i + j] - z;
          a[i + j] = a[i + j] + z;
        }
    if (sg)
      for (int i = 0; i < n; ++i) a[i] /= n;
  }
  template <class T>
  vector<long long> multiply(const vector<T> &a, const vector<T> &b) {
    int need = a.size() + b.size() - 1;
    int nb = 1;
    while ((1 << nb) < need) ++nb;
    ensure_base(nb);
    int sz = 1 << nb;
    vector<CP> fa(sz), fb(sz);
    for (int i = 0; i < sz; ++i) {
      if (i < a.size()) fa[i] = CP(a[i], 0);
      if (i < b.size()) fb[i] = CP(b[i], 0);
    }
    fft(fa, sz);
    fft(fb, sz);
    for (int i = 0; i < sz; ++i) fa[i] *= fb[i];
    fft(fa, sz, 1);
    vector<long long> res(need);
    for (int i = 0; i < need; ++i) res[i] = llround(fa[i].x);
    return res;
  }
};