#include <stdbool.h>
#include <stdio.h>

int t, n, k, b;
int a[128] = {};

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &k);
    bool ok = true;  // trueなら”wa-i”,falseなら”e-n”
    for (int i = 1; i <= k; i++)
      scanf("%d", &a[i]);  // a[i] :手持ちの i番目のキャンディーの個数
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &b);
      a[b] = a[b] - 1;  //おねだりされたので手持ちの個数が1つ減る
      if (a[b] < 0)
        ok = false;  //負になっていたらおねだりに応えられなかったということ
    }
    if (ok)
      printf("wa-i\n");
    else
      printf("e-n\n");
  }
  return 0;
}