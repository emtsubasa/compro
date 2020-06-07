#include <bits/stdc++.h>
using namespace std;

long long n, q;
vector<int> a;
set<int> st;

void numswap(int x);

int main() {
  cin >> n >> q;
  for (int i = 0; i < n; ++i) a.push_back(i);
  for (int i = 0; i < q; ++i) {
    int t, x, y;
    cin >> t >> x >> y;
    if (t == 1)
      numswap(x);
    else
      while (1) {
        auto it = st.lower_bound(x);
        if (it == st.end() || *it >= y) break;
        numswap(*it);
      }
  }
  for (int i = 0; i < n; ++i) {
    if (i != 0) cout << " ";
    cout << a[i] + 1;
  }
  cout << endl;
  return 0;
}

void numswap(int x) {
  swap(a[x - 1], a[x]);
  for (int j = x - 1; j <= x + 1; ++j)
    if (j > 0 && j <= n - 1) {
      if (a[j - 1] > a[j])
        st.insert(j);
      else
        st.erase(j);
    }
}