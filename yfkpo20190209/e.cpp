#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

// distance between (x1,y1) and (x2,y2)
double cdis(double x1, double y1, double x2, double y2) {
  return sqrtl((x1 - x2) * (x1 - x2) +
               (y1 - y2) * (y1 - y2));
}
int n;
double d;
pair<long long, long long> mp[1005];
int bf[1005] = {0};

void solve();

int main() {
  cin >> n >> d;
  for(int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    mp[i] = make_pair(x, y);
  }
  solve();
  return 0;
}

void solve() {
  for(int i = 1; i < n; ++i) bf[i] = -1;
  vector<int> ans;
  queue<int> qu;
  int now;
  qu.push(0);
  while(!qu.empty()) {
    now = qu.front();
    qu.pop();
    for(int i = 0; i < n; ++i)
      if(i != now && bf[i] == -1 &&
         d >= cdis(mp[now].fi, mp[now].se, mp[i].fi,
                   mp[i].se)) {
        qu.push(i);
        bf[i] = now;
      }
  }
  now = n - 1;
  while(now != 0) {
    ans.push_back(now);
    now = bf[now];
  }
  ans.push_back(0);
  for(int i = 0; i < ans.size(); ++i)
    cout << ans[ans.size() - 1 - i] + 1 << endl;
}