// 0-indexed
template <class T>
struct BIT {
  int treesize;
  vector<T> lst;
  // constructor
  BIT(int newn = 0) : treesize(newn), lst(newn + 1, 0) {}
  // a_place += num
  void add(int place, T num) {
    ++place;
    while (place <= treesize) {
      lst[place] += num;
      place += place & -place;
    }
  }
  // sum between [0,place)
  T sum(int place) {
    T res = 0;
    while (place > 0) {
      res += lst[place];
      place -= place & -place;
    }
    return res;
  }
  // sum [l,r)
  T sum(int left, int right) { return sum(right) - sum(left); }
};