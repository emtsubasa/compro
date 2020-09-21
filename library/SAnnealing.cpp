#define LIMTIME 1930
const double STTEMP = 250, ENDTEMP = 5;
const long long SAINF = 1e18;

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
void SA() {
  auto start = chrono::system_clock::now();
  auto nowt = chrono::system_clock::now();
  auto dur = nowt - start;
  auto msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
  while (msec < LIMTIME) {
    long long BFSCORE = 0, NOWSCORE = 0;
    /* SA pattern
    double TEMPERATURE = STTEMP + (ENDTEMP - STTEMP) * msec / LIMTIME;
    double PROBABLE = exp((NOWSCORE - BFSCORE) / TEMPERATURE);
    if (PROBABLE <= (xorshift() % SAINF) / (double)SAINF) {
      // return to before state
    }
    //*/
    //* climbing pattern
    if (NOWSCORE < BFSCORE) {
      // return to before score
    }
    //*/
    nowt = chrono::system_clock::now();
    dur = nowt - start;
    msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
  }
}