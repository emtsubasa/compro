#include <bits/stdc++.h>
using namespace std;

long long n, req[3] = {};

int main() {
  cin >> n;
  for (int i = 0; i < 3; ++i) cin >> req[i];
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    if (s == "PROGRAM")
      --req[0];
    else if (s == "CG")
      --req[1];
    else
      --req[2];
  }
  bool ch = 1;
  for (int i = 0; i < 3; ++i)
    if (req[i] > 0) ch = 0;
  if (ch)
    cout << "Happy" << endl;
  else
    cout << "Unhappy" << endl;
  return 0;
}