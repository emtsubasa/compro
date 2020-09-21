n, m, k, f = map(int, input().split())
MOD = 998244353
cnt = [0] * k
frees = 0
for _ in range(m):
    y, x, z = map(int, input().split())
    if abs(y-x) <= 1:
        for i in range(k):
            if (z >> i) & 1 == 1:
                cnt[i] += 1
    else:
        frees += 1
res = pow(1 << k,n * n - 3 * n + 2 - frees,MOD)
m -= frees
for i in range(k):
    now = 0
    if cnt[i] == 0:
        now += 1
    if (f >> i) & 1 == 1:
        res = (res * (pow(2,3 * n - 2 - m,MOD) + MOD - now)) % MOD
    else:
        res = (res * now) % MOD
print(res)

