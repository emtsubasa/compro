#include <bits/stdc++.h>
using namespace std;

long long n, k, r, f;
string res = "Neutral";

int main() {
  cin >> n >> k >> r >> f;
  if (k == n)
    res = "Genocide";
  else if (f == n)
    res = "True Pacifist";
  cout << res << endl;
  return 0;
}