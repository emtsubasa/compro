MOD = (10 ** 9) + 7
n = int(input())
a = list(map(int,input().split()))
fact = [1] * n
rfact = [1] * n
for i in range(1,n):
    fact[i] = fact[i - 1] * i % MOD
rfact[n-1] = pow(fact[n - 1], MOD-2, MOD)
for i in range(n-2,1,-1):
    rfact[i] = rfact[i + 1] * (i + 1) % MOD

def com(p, q):
    if q < 0 or p < q:
         return 0
    return fact[p] * rfact[q] * rfact[p-q] % MOD

res = 0
for i in range(1,n):
    diff = abs(a[i] - a[i - 1])
    res += diff * com(n-2,i-1) % MOD
    res %= MOD

print(res)