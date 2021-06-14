template <typename T = int, typename D = int>
struct BinaryTrie {
  struct Node {
    Node *par, *to[2];
    D cnt;
    Node() : par(nullptr), to{nullptr, nullptr}, cnt(D(0)) {}
  };
  int max_dep;
  Node *root;
  BinaryTrie(int _max_dep = 31) : max_dep(_max_dep), root(new Node()) {}
  constexpr void insert(T x, D num = 1, T xor_val = 0) noexcept {
    x ^= xor_val;
    Node *v = root;
    v->cnt += num;
    for (int i = max_dep - 1; i >= 0; --i) {
      int b = x >> i & 1;
      if (!(v->to[b])) {
        v->to[b] = new Node();
        v->to[b]->par = v;
      }
      v = v->to[b];
      v->cnt += num;
    }
  }
  constexpr void erase(const T &x, D num = 1, T xor_val = 0) noexcept {
    auto v = find(x ^ xor_val);
    if (!v) return;
    num = min(num, v->cnt);
    v->cnt -= num;
    for (int i = 0; i < max_dep; ++i) {
      int b = x >> i & 1;
      auto p = v->par;
      if (!(v->cnt)) p->to[b] = nullptr, v->par = nullptr;
      v = p, v->cnt -= num;
    }
  }
  constexpr D count(T x, T xor_val = 0) noexcept {
    auto v = find(x ^ xor_val);
    return v ? v->cnt : 0;
  }
  constexpr Node *find(T x) noexcept {
    Node *v = root;
    for (int i = max_dep - 1; i >= 0; --i) {
      int b = x >> i & 1;
      if (!(v->to[b])) return nullptr;
      v = v->to[b];
    }
    return v;
  }
  //   0-inxeded
  constexpr T kth_element(D k, T xor_val = 0) const noexcept {
    assert(k < root->cnt);
    Node *v = root;
    T res = 0;
    for (int i = max_dep - 1; i >= 0; --i) {
      int b = (xor_val >> i & 1);
      if (!(v->to[b]) || v->to[b]->cnt <= k) {
        if (v->to[b]) k -= v->to[b]->cnt;
        b ^= 1;
      }
      res <<= 1;
      res |= b;
      v = v->to[b];
    }
    assert(v->cnt > k);
    return res ^ xor_val;
  }
  constexpr T min_element(T xor_val = 0) const noexcept {
    return kth_element(0, xor_val);
  }
  constexpr T max_element(T xor_val = 0) const noexcept {
    return kth_element(root->cnt - 1, xor_val);
  }
};
