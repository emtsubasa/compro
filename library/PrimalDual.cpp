template <class T>
struct Primal_Dual {
  using Pa = pair<T, int>;
  int infinity = (int)(1e9);
  struct edge {
    int to;
    T cap, cost;
    int rev;
  };
  int v;
  vector<vector<edge>> edges;
  vector<T> h;
  vector<T> dist;
  vector<int> prevv, preve;
  Primal_Dual(int vsize = 1) {
    v = vsize;
    edges.resize(v);
    h.resize(v);
    dist.resize(v);
    prevv.resize(v);
    preve.resize(v);
  }
  bool add(int from, int to, T cap, T cost) {
    edges[from].push_back((edge){to, cap, cost, (int)edges[to].size()});
    edges[to].push_back((edge){from, 0, -cost, (int)edges[from].size() - 1});
    return 1;
  }
  T solve(int s, int t, T f) {
    T ans = 0;
    h.assign(v, 0);
    while (f > 0) {
      priority_queue<Pa, vector<Pa>, greater<Pa>> qu;
      dist.assign(v, infinity);
      dist[s] = 0;
      qu.push({0, s});
      while (!qu.empty()) {
        Pa now = qu.top();
        qu.pop();
        int nowv = now.second;
        if (dist[nowv] < now.first) continue;
        for (int i = 0; i < (int)edges[nowv].size(); ++i) {
          edge &e = edges[nowv][i];
          if (e.cap > 0 &&
              dist[e.to] > dist[nowv] + e.cost + h[nowv] - h[e.to]) {
            dist[e.to] = dist[nowv] + e.cost + h[nowv] - h[e.to];
            prevv[e.to] = nowv;
            preve[e.to] = i;
            qu.push({dist[e.to], e.to});
          }
        }
      }
      if (dist[t] == infinity) return -1;
      for (int i = 0; i < v; ++i) h[i] += dist[i];
      T d = f;
      for (int i = t; i != s; i = prevv[i])
        d = min(d, edges[prevv[i]][preve[i]].cap);
      f -= d;
      ans += d * h[t];
      for (int i = t; i != s; i = prevv[i]) {
        edge &e = edges[prevv[i]][preve[i]];
        e.cap -= d;
        edges[i][e.rev].cap += d;
      }
    }
    return ans;
  }
};