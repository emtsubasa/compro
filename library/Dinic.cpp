template <class T>
struct Dinic {
  struct edge {
    int to;
    T cap;
    int rev;
    edge(int t = 0, T c = 0, int r = -1) : to(t), cap(c), rev(r) {}
  };
  int n;
  T finf;
  vector<vector<edge>> g;
  vector<int> id;
  vector<int> d;
  Dinic(int _n = 1, T _finf = (int)(2e9))
      : n(_n), finf(_finf), g(n, vector<edge>()), id(n), d(n) {}

  int add(int start, int goal, T capacity) {
    g[start].emplace_back(goal, capacity, (int)g[goal].size());
    g[goal].emplace_back(start, 0, (int)g[start].size() - 1);
    return (int)g[start].size() - 1;
  }

  T change(int x, int idx, T newf, int s, int t) {
    int y = g[x][idx].to, ridx = g[x][idx].rev;
    newf -= g[x][idx].cap + g[y][ridx].cap;
    if (newf > 0) {
      g[x][idx].cap += newf;
      return solve(s, t);
    } else if (newf < 0) {
      g[x][idx].cap += newf;
      if (g[x][idx].cap >= 0) return T(0);
      swap(newf = 0, g[x][idx].cap);
      g[y][ridx].cap += newf;
      newf += solve(x, y, -newf);
      if (-newf) {
        solve(x, s, -newf);
        solve(t, y, -newf);
      }
      return newf;
    }
    return T(0);
  }

  void bfs(int st) {
    d.assign(n, -1);
    queue<int> qu;
    d[st] = 0;
    qu.push(st);
    while (qu.size()) {
      int now = qu.front();
      qu.pop();
      for (auto e : g[now])
        if (e.cap > 0 && d[e.to] < 0) {
          d[e.to] = d[now] + 1;
          qu.push(e.to);
        }
    }
  }
  T pathdfs(int now, int goal, T nf) {
    if (now == goal) return nf;
    int len = g[now].size();
    for (int& i = id[now]; i < len; ++i) {
      edge* e = &g[now][i];
      if (e->cap > 0 && d[now] < d[e->to]) {
        T res = pathdfs(e->to, goal, min(nf, e->cap));
        if (res > 0) {
          e->cap -= res;
          g[e->to][e->rev].cap += res;
          return res;
        }
      }
    }
    return 0;
  }
  T solve(int start, int goal, T flimit = 0) {
    if (!flimit) flimit = finf;
    T res = 0, nf = 0;
    while (flimit - res) {
      bfs(start);
      if (d[goal] < 0) return res;
      id.assign(n, 0);
      while ((nf = pathdfs(start, goal, flimit - res)) > 0) res += nf;
    }
    return res;
  }
};