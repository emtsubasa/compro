#include <bits/stdc++.h>
using namespace std;

// calculate |gcd|.
// if  ether num is 0, return 0
long long GCD(long long left, long long right) {
  if(left == 0 || right == 0) return 0;
  if(left < 0) left *= -1;
  if(right < 0) right *= -1;
  if(left < right) swap(left, right);
  long long nextnum, ansgcd = -1;
  while(ansgcd == -1) {
    nextnum = left % right;
    if(nextnum == 0) ansgcd = right;
    left = right;
    right = nextnum;
  }
  return ansgcd;
}

long long LCM(long long left, long long right) {
  return left / GCD(left, right) * right;
}
int n;
int s[105] = {0};
int t[105] = {0};
int ans[105][2] = {0};

void solve();

int main() {
  cin >> n;
  for(int i = 0; i < n; ++i) cin >> s[i];
  for(int i = 0; i < n; ++i) cin >> t[i];
  solve();
  for(int i = 0; i < n; ++i)
    cout << ans[i][0] << " " << ans[i][1] << endl;
  return 0;
}

void solve() {
  ans[0][0] = ans[1][1] = 1;
  for(int i = 0; i < n; ++i) {
    int gcd = GCD(s[0], s[i] - t[i]);
    ans[i][0] = (s[i] - t[i]) / gcd;
    ans[i][1] = s[0] / gcd;
  }
}