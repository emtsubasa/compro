#include <bits/stdc++.h>
using namespace std;

// 0-indexed
// now node k
// child node k*2+1 and k*2+2
// parent node (k-1)/2
struct data {
  long long a;
};
const long long minint = 0;
data resetdata = {minint};
struct RMQ {
  // except bottom size
  int sizen;
  vector<data> dat;
  RMQ(int newn = 1, data resets = resetdata) {
    reset(newn, resets);
  }
  void reset(int newn = 1, data resets = resetdata) {
    sizen = 1;
    while(sizen < newn) sizen *= 2;
    dat.resize(2 * sizen - 1);
    for(int i = 0; i < dat.size(); ++i) dat[i] = resets;
  }
  // "go up" process
  // data[k].a = newnum
  bool update(int k, long long newnum) {
    k += sizen - 1;
    dat[k].a = newnum;
    while(k > 0) {
      k = (k - 1) / 2;
      dat[k].a = max(dat[k * 2 + 1].a, dat[k * 2 + 2].a);
    }
    return 1;
  }
  // "go down" process
  // return min number in [a,b)
  // pick(a,b,0,0,sizen)
  long long pick(int a, int b, int k = 0, int l = 0,
                 int r = -1) {
    if(r == -1) r = sizen;
    // [l,r)[a,b) or [a,b)[l,r)
    if(r <= a || b <= l) return minint;
    // [a,[l,r),b)
    if(a <= l && r <= b) return dat[k].a;
    // else
    long long nowl, nowr, nextlr = k * 2 + 1,
                          med = (l + r) / 2;
    nowl = pick(a, b, nextlr, l, med);
    nowr = pick(a, b, nextlr + 1, med, r);
    return max(nowl, nowr);
  }
};

int n, k;
long long f[100005] = {0};
RMQ rmq;

long long solve();

int main() {
  cin >> n >> k;
  rmq = RMQ(n + 1);
  for(int i = 0; i < n; ++i) cin >> f[i];
  for(int i = 1; i <= n; ++i) {
    int b;
    cin >> b;
    rmq.update(i, b);
  }
  cout << solve() << endl;
  return 0;
}

long long solve() {
  long long ans = 0;
  for(int i = 0; i < n; ++i) {
    ans = max(ans, f[i] + rmq.pick(max(0, i + 1 - k),
                                   min(n + 1, i + 2 + k)));
  }
  return ans;
}