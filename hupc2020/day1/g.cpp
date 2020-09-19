#include <bits/stdc++.h>
#define inf (long long)(1e17)
using namespace std;

struct dat {
  long long mi, ma, ad, fin;
  bool ch;
  dat(long long _i = inf, long long _a = -inf, long long _d = 0)
      : mi(_i), ma(_a), ad(_d), fin(inf), ch(0) {}
};

const int blen = 400;
int n, q;
vector<long long> a, bucket;
vector<dat> info;

long long calc(const dat& d, long long x) {
  if (d.ch) return d.fin + d.ad;
  x = min(x, d.mi);
  x = max(x, d.ma);
  return x + d.ad;
}
void update(dat& d, int t, long long x) {
  if (t == 3)
    d.ad += x;
  else {
    if (d.ch) {
      if (t == 1)
        d.fin = min(d.fin, x - d.ad);
      else
        d.fin = max(d.fin, x - d.ad);
      return;
    }
    if (t == 1)
      d.mi = min(d.mi, d.fin = x - d.ad);
    else
      d.ma = max(d.ma, d.fin = x - d.ad);
    if (d.mi <= d.ma) d.ch = 1;
  }
}

void blockupdate(int id) {
  int fin = min(n, (id + 1) * blen);
  for (int i = id * blen; i < fin; ++i) a[i] = calc(info[id], a[i]);
  info[id] = dat();
}

long long blockcount(int id, long long l, long long r) {
  auto cmp = [](long long x, long long y, bool isupper) {
    if (isupper) return x < y;
    return x <= y;
  };
  auto f = [&](long long lid, long long rid, long long x, bool isupper = 0) {
    if (cmp(x, a[bucket[lid]], isupper)) return lid;
    while (rid - lid > 1) {
      long long mid = (lid + rid) >> 1;
      if (cmp(x, a[bucket[mid]], isupper))
        rid = mid;
      else
        lid = mid;
    }
    return rid;
  };
  long long res = 0;
  l -= info[id].ad, r -= info[id].ad;
  if (info[id].ch) return blen * (l <= info[id].fin && info[id].fin <= r);

  int lid = id * blen, rid = (id + 1) * blen;
  int now = f(lid, rid, info[id].ma, 1);
  if (l <= info[id].ma && info[id].ma <= r) res += now - lid;
  lid = now;
  now = f(lid, rid, info[id].mi);
  if (l <= info[id].mi && info[id].mi <= r) res += rid - now;
  rid = now;
  res += f(lid, rid, r, 1) - lid;
  res -= f(lid, rid, l) - lid;
  return res;
}

int main() {
  cin >> n >> q;
  a.resize(n);
  bucket.resize(n);
  iota(bucket.begin(), bucket.end(), 0);
  for (auto& p : a) cin >> p;
  for (int i = 0; i < n; i += blen) {
    int r = min(n, i + blen);
    sort(bucket.begin() + i, bucket.begin() + r,
         [](long long l, long long r) { return a[l] < a[r]; });
  }
  info.resize((n + blen - 1) / blen);
  while (q--) {
    long long t, l, r, x, y;
    cin >> t >> l >> r >> x;
    --l;
    if (t <= 3) {
      auto f = [](long long l, long long r) { return a[l] < a[r]; };
      dat d;
      update(d, t, x);
      if (l < r && l % blen != 0) {
        blockupdate(l / blen);
        while (l < r && l % blen != 0) {
          a[l] = calc(d, a[l]);
          ++l;
        }
        int id = (l - 1) / blen;
        sort(bucket.begin() + id * blen,
             bucket.begin() + min(n, (id + 1) * blen), f);
      }
      if (l < r && r % blen != 0) {
        blockupdate((r - 1) / blen);
        while (l < r && r % blen != 0) {
          --r;
          a[r] = calc(d, a[r]);
        }
        int id = r / blen;
        sort(bucket.begin() + id * blen,
             bucket.begin() + min(n, (id + 1) * blen), f);
      }
      l /= blen, r /= blen;
      for (int i = l; i < r; ++i) update(info[i], t, x);

    } else {
      long long res = 0;
      cin >> y;
      while (l < r && l % blen != 0) {
        long long now = calc(info[l / blen], a[l]);
        if (x <= now && now <= y) ++res;
        ++l;
      }
      while (l < r && r % blen != 0) {
        --r;
        long long now = calc(info[r / blen], a[r]);
        if (x <= now && now <= y) ++res;
      }
      l /= blen, r /= blen;
      for (int i = l; i < r; ++i) res += blockcount(i, x, y);
      cout << res << endl;
    }
  }
  return 0;
}
