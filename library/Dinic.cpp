#define inf 2000000000  // 1e17
template <class T>
struct Dinic {
  struct edge {
    int to;
    T cap;
    int rev;
  };
  vector<vector<edge>> edges;
  vector<int> id;
  vector<int> d;
  Dinic(int n = 1) {
    edges.clear();
    edges.resize(n);
    id.resize(n);
    d.resize(n);
  }
  bool add(int start, int goal, T capacity) {
    edges[start].push_back((edge){goal, capacity, (int)edges[goal].size()});
    edges[goal].push_back((edge){start, 0, (int)edges[start].size() - 1});
    return 1;
  }
  void bfs(int st) {
    d.assign(d.size(), -1);
    queue<int> qu;
    d[st] = 0;
    qu.push(st);
    while (qu.size()) {
      int now = qu.front();
      qu.pop();
      for (auto e : edges[now])
        if (e.cap > 0 && d[e.to] < 0) {
          d[e.to] = d[now] + 1;
          qu.push(e.to);
        }
    }
  }
  T pathdfs(int now, int goal, T nf) {
    if (now == goal) return nf;
    for (int& i = id[now]; i < (int)edges[now].size(); ++i) {
      edge* e = &edges[now][i];
      if (e->cap > 0 && d[now] < d[e->to]) {
        T res = pathdfs(e->to, goal, min(nf, e->cap));
        if (res > 0) {
          e->cap -= res;
          edges[e->to][e->rev].cap += res;
          return res;
        }
      }
    }
    return 0;
  }
  T solve(int start, int goal) {
    T res = 0, nf = 0;
    while (1) {
      bfs(start);
      if (d[goal] < 0) return res;
      id.assign(id.size(), 0);
      while ((nf = pathdfs(start, goal, inf)) > 0) res += nf;
    }
    return -1;
  }
};