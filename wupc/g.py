N, K, T = map(int,input().split())
t = [0] * N
p = [0] * max(N,T + 1)
for i in range(N):
    t[i], p[i] = map(int,input().split())
dp = [0] * (T + 1)
for i in range(N):
    for j in range(T, t[i] - 1 , -1):
        dp[j] = max(dp[j],dp[j-t[i]] + p[i])
for i in range(T + 1):
    p[i] = dp[i]
for i in range(T + 1):
    nt = i + K
    for j in range(nt, T + 1):
        dp[j] = max(dp[j],dp[j-nt] + p[i])
res = 0
for i in range(T + 1):
    res = max(res,dp[i])
print(res)