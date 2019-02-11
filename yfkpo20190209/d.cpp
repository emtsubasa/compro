#include <bits/stdc++.h>
#define fi first
#define se second
#define N 1000000007
using namespace std;

long long n, m;
long long dp[10005] = {0};
long long dis[10005] = {0};
vector<pair<long long, long long>> edges[10005];
priority_queue<pair<long long, long long>,
               vector<pair<long long, long long>>,
               greater<pair<long long, long long>>>
    pq;

long long solve();

int main() {
  cin >> n >> m;
  for(int i = 0; i < m; ++i) {
    long long s, t, c;
    cin >> s >> t >> c;
    --s, --t;
    edges[s].push_back(make_pair(c, t));
    edges[t].push_back(make_pair(c, s));
  }
  cout << solve() << endl;
  return 0;
}

long long solve() {
  for(int i = 1; i < n; ++i) dis[i] = 1000000000000;
  dp[0] = 1;
  pq.push(make_pair(0, 0));
  while(!pq.empty()) {
    pair<long long, long long> now = pq.top(), nextn, nowe;
    pq.pop();
    if(now.fi != dis[now.se]) continue;
    for(int i = 0; i < edges[now.se].size(); ++i) {
      nowe = edges[now.se][i];
      nextn = now;
      nextn.se = nowe.se;
      nextn.fi += nowe.fi;
      if(dis[nextn.se] > nextn.fi) {
        dp[nextn.se] = 0;
        dis[nextn.se] = nextn.fi;
        pq.push(nextn);
      }
      if(dis[nextn.se] == nextn.fi) {
        dp[nextn.se] += dp[now.se];
        dp[nextn.se] %= N;
      }
    }
  }
  return dp[n - 1];
}