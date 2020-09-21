unsigned int xorshift() {
  static unsigned int nowx = 123456789, nowy = 362436069, nowz = 521288629,
                      noww = 88675123;
  unsigned int temp;
  temp = (nowx ^ (nowx << 11));
  nowx = nowy;
  nowy = nowz;
  nowz = noww;
  return (noww = (noww ^ (noww >> 19)) ^ (temp ^ (temp >> 8)));
}