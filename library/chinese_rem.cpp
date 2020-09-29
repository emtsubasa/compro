// as + bt = GCD(a,b) a,b:const s,t:var(any)
// return GCD(a,b)
long long extGCD(long long a, long long b, long long& s, long long& t) {
  s = 1, t = 0;
  long long u = 0, v = 1;
  while (b) {
    long long tmp = a / b;
    a -= b * tmp;
    s -= u * tmp;
    t -= v * tmp;
    swap(s, u);
    swap(t, v);
    swap(a, b);
  }
  return a;
}
// (mod)x+ay=1, calculate y -> a^-1 (mod m) (a,m : coprime)
long long calcinv(long long a, long long m) {
  long long s, t;
  extGCD(a, m, s, t);
  return (s + m) % m;
}

// x=b_i(mod m_i) calc min x,lcm(m_i).
// if not exist, return (-1,-1)
pair<long long, long long> chinese_rem(const vector<long long>& b,
                                       const vector<long long>& m) {
  long long r = 0, lcm = 1;
  assert(b.size() == m.size());
  long long bsize = b.size();
  for (int i = 0; i < bsize; ++i) {
    long long p, q, d, now;
    d = extGCD(lcm, m[i], p, q);
    if ((b[i] - r) % d != 0) return make_pair(-1, -1);
    now = (b[i] - r) / d * p % (m[i] / d);
    r += lcm * now;
    lcm *= m[i] / d;
  }
  return make_pair((r + lcm) % lcm, lcm);
}

// x=b_i(mod m_i) calc min x(mod nowMOD).
// if not exist, return -1
long long garner(vector<long long>& b, vector<long long>& m,
                 long long nowMOD = 9223372036854775807LL) {
  assert(b.size() == m.size());
  // prepair, O(N^2)
  // if m_i are coprime, don't have to do it
  long long bsize = b.size(), msize = m.size() + 1, dummy1, dummy2;
  for (int i = 0; i < bsize; ++i)
    for (int j = 0; j < i; ++j) {
      long long g = extGCD(m[i], m[j], dummy1, dummy2);
      if ((b[i] - b[j]) % g != 0) return -1;
      m[i] /= g;
      m[j] /= g;
      long long gi = extGCD(m[i], g, dummy1, dummy2), gj;
      gj = g / gi;
      do {
        g = extGCD(gi, gj, dummy1, dummy2);
        gi *= g, gj /= g;
      } while (g != 1);
      m[i] *= gi, m[j] *= gj;
      b[i] %= m[i], b[j] %= m[j];
    }
  // calc
  m.push_back(nowMOD);
  vector<long long> coeffs(msize, 1);
  vector<long long> constants(msize, 0);
  for (int k = 0; k < bsize; ++k) {
    long long tmp = (b[k] - constants[k]) % m[k];
    long long t = (tmp + m[k]) % m[k] * calcinv(coeffs[k], m[k]) % m[k];
    for (int i = k + 1; i < msize; ++i) {
      (constants[i] += t * coeffs[i] % m[i]) %= m[i];
      (coeffs[i] *= m[k]) %= m[i];
    }
  }
  return constants.back();
}