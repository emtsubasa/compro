template <typename T = int>
struct SlopeTrick {
  T minf, inf, addl, addr;
  priority_queue<T> pql;
  priority_queue<T, vector<T>, greater<T>> pqr;
  SlopeTrick(T _inf = 1e9) : minf(0), inf(_inf), addl(0), addr(0) {
    pql.push(-inf);
    pqr.push(inf);
  }

  void pushL(const T &a) { pql.push(a - addl); }
  T topL() const { return pql.top() + addl; }
  T popL() {
    T res = topL();
    pql.pop();
    return res;
  }
  void pushR(const T &a) { pqr.push(a - addr); }
  T topR() const { return pqr.top() + addr; }
  T popR() {
    T res = topR();
    pqr.pop();
    return res;
  }
  size_t size() { return pql.size() + pqr.size(); }

  // min f(x)
  T get_minf() { return minf; }
  T get_minx() { return pql.top(); }
  T get_maxx() { return pqr.top(); }
  T get_fx(const T &x) {
    T res = minf;
    while (pql.size()) res += max(T(0), popL() - x);
    while (pqr.size()) res += max(T(0), x - popR());
    return res;
  }
  // f(x) += a
  void add_all(const T &a) { minf += a; }
  // add f(x) = max(0, x-a), _/
  void add_xa(const T &a) {
    minf += max(T(0), topL() - a);
    pushL(a);
    pushR(popL());
  }
  // add f(x) = max(0, a-x), \_
  void add_ax(const T &a) {
    minf += max(T(0), a - topR());
    pushR(a);
    pushL(popR());
  }
  // add f(x) = abs(x-a) = max(0, x-a) + max(0, a-x), \/
  void add_abs(const T &a) { add_xa(a), add_ax(a); }
  // f(x) := min f(y) (y >= x), \/ -> _/
  void clear_left() { pql.clear(); }
  // f(x) := min f(y) (y <= x), \/ -> \_
  void clear_right() { pqr.clear(); }
  // f(x) = min f(y) (x-b <= y <= x-a), \/ -> \_/
  void shift(const T &a, const T &b) {
    assert(a <= b);
    addl += a, addr += b;
  }
  // f(x) = f(x-a), \/. -> .\/
  void shift(const T &a) { shift(a, a); }
  // f(x) = f(x) + g(x)
  void merge(SlopeTrick &st) {
    if (st.size() > size()) {
      swap(st.pql, pql), swap(st.pqr, pqr);
      swap(st.addl, addl), swap(st.addr, addr), swap(st.minf, minf);
    }
    while (st.pqr.size()) add_xa(st.popR());
    while (st.pql.size()) add_ax(st.popL());
    minf += st.minf;
  }
};