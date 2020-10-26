// res[i] = sum j \in i v[j](if upper, swap(i, j))
template <class T>
vector<T> fast_zeta_transform(int n, vector<T> v, bool upper = 0) {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < (1 << n); ++j)
      if ((j >> i & 1) ^ upper) v[j] += v[j ^ (1 << i)];
  return v;
}