template <class T>
vector<int> manacher(const T &s) {
  vector<int> res;
  int i = 0, j = 0, len = s.size();
  res.assign(len, 0);
  while (i < len) {
    while (i - j >= 0 && i + j < len && s[i - j] == s[i + j]) ++j;
    res[i] = j;
    int k = 1;
    while (i - k >= 0 && k + res[i - k] < j) res[i + k] = res[i - k], ++k;
    i += k, j -= k;
  }
  return res;
}