template <class T>
vector<int> z_algorithm(const T &s) {
  vector<int> res;
  int i = 1, j = 0, len = s.size();
  res.resize(s.size());
  res[0] = len;
  while (i < len) {
    while (i + j < len && s[j] == s[i + j]) ++j;
    res[i] = j;
    if (j == 0) {
      ++i;
      continue;
    }
    int k = 1;
    while (i + k < len && k + res[k] < j) res[i + k] = res[k], ++k;
    i += k, j -= k;
  }
  return res;
}