template <class T>
struct UnionfindW {
  // tree number
  vector<int> par;
  // tree rank
  vector<int> treerank;
  // edge weight
  vector<T> weight;
  const int inf = 2147483647;
  // constructor
  UnionfindW(int n = 1, T initialnum = 0) { stree(n + 1, initialnum); }
  // make and initialization
  void stree(int n = 1, T initialnum = 0) {
    par.assign(n, -1);
    treerank.assign(n, 0);
    weight.assign(n, initialnum);
  }
  // search root
  int root(int x) {
    if (par[x] < 0) return x;
    int rx = root(par[x]);
    weight[x] += weight[par[x]];
    return par[x] = rx;
  }
  // is same?
  bool issame(int x, int y) { return root(x) == root(y); }
  // calculate weight
  T calcw(int x) {
    root(x);
    return weight[x];
  }
  // add
  // x+w = y
  // already added, return 0
  bool uni(int x, int y, T w = 0) {
    w += calcw(x);
    w -= calcw(y);
    x = root(x);
    y = root(y);
    if (x == y) return 0;
    if (treerank[x] > treerank[y]) swap(x, y);
    if (treerank[x] == treerank[y]) ++treerank[x];
    par[y] -= size(x);
    par[x] = y;
    weight[x] = -w;
    return 1;
  }

  int size(int x) { return -par[root(x)]; }

  // calculate difference between x and y (y-x)
  // if not same tree, return 1
  T calcdiff(int x, int y) {
    if (!issame(x, y)) return inf;
    return calcw(y) - calcw(x);
  }
};