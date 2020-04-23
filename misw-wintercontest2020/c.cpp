#include <bits/stdc++.h>
using namespace std;

struct Prime {
  vector<bool> ch;
  vector<long long> ary;
  Prime(long long N = 2000000) {
    ch.resize(N + 1);
    ch[0] = ch[1] = 1;
    for (int i = 2; i <= N; ++i)
      if (!ch[i]) {
        ary.push_back(i);
        for (int j = 2; (long long)i * j <= N; ++j) ch[i * j] = 1;
      }
  }
  inline const bool isprime(int n) { return !ch[n]; }
  inline const long long &operator[](int k) const { return (ary[k]); }
};

long long q;
Prime pr;
vector<long long> lst = pr.ary;

int main() {
  for (int i = 1; i < lst.size(); ++i) {
    lst[i] += lst[i - 1];
  }
  cin >> q;
  while (q--) {
    long long a, b, res;
    cin >> a >> b;
    res = lst[b - 1];
    if (a >= 2) res -= lst[a - 2];
    cout << res << endl;
  }
  return 0;
}