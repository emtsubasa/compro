#include <bits/stdc++.h>
using namespace std;

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

long long mod_pow(long long base, int e, int mod) {
  long long res = 1;
  while (e) {
    if (e & 1) (res *= base) %= mod;
    (base *= base) %= mod;
    e >>= 1;
  }
  return res;
}

int n, m, q, all = 1;
vector<int> mul;

int main() {
  cin >> n >> m >> q;
  {  // input and pre calc
    mul.assign(2 * m + 1, 1);
    for (int i = 1; i <= 2 * m; ++i) {
      if (i <= m) {
        cin >> mul[i];
        mul[i] = mul[i + m] = calcinv(mul[i], n);
        all = 1LL * all * mul[i] % n;
      }
      mul[i] = 1LL * mul[i - 1] * mul[i] % n;
    }
  }
  auto calc = [](int l, int r) {
    return 1LL * mul[r] * calcinv(mul[l], n) % n;
  };
  for (int i = 0; i < q; ++i) {
    int x, y, z, e;
    cin >> x >> y >> z;
    --y;
    e = 1LL * mod_pow(all, z / m, n) * calc(y, y + z % m) % n;
    cout << mod_pow(x, e, n + 1) << endl;
  }
  return 0;
}
