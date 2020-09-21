// calculate |gcd|.
// if  ether num is 0, return 0
long long GCD(long long left, long long right) {
  if (left == 0 || right == 0) return 0;
  if (left < 0) left *= -1;
  if (right < 0) right *= -1;
  if (left < right) swap(left, right);
  long long nextnum, ansgcd = -1;
  while (ansgcd == -1) {
    nextnum = left % right;
    if (nextnum == 0) ansgcd = right;
    left = right;
    right = nextnum;
  }
  return ansgcd;
}

long long LCM(long long left, long long right) {
  return left / GCD(left, right) * right;
}
