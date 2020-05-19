#include <stdio.h>

int n, t;
int y[512] = {}, k[512] = {};

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    int win = 0, lose = 0, draw = 0;
    for (int i = 0; i < n; i++) scanf("%d", &y[i]);  //あなたの手の入力
    for (int i = 0; i < n; i++) scanf("%d", &k[i]);  //勝太郎くんの手の入力
    for (int i = 0; i < n; i++) {
      int diff = k[i] - y[i];
      if (diff == 1 || diff == -2)
        ++win;
      else if (diff == 2 || diff == -1)
        ++lose;
      else
        ++draw;
    }
    printf("%d %d %d\n", win, lose, draw);
  }
  return 0;
}