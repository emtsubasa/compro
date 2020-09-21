MOD = (10 ** 9) + 7
l = 10 ** 5
fact = [1] * l
rfsum = [1] * l
for i in range(1,l):
    fact[i] = fact[i - 1] * i % MOD
rfsum[l-1] = pow(fact[l - 1], MOD-2, MOD)
for i in range(l-2,1,-1):
    rfsum[i] = rfsum[i + 1] * (i + 1) % MOD
for i in range(1,l):
    rfsum[i] += rfsum[i-1] 
    rfsum[i] %= MOD


n = int(input())

# divisors
divisors = []
id = 1
while id ** 2 <= n:
    if n % id == 0:
        divisors.append(id)
        if id ** 2 != n:
            divisors.append(n//id)
    id += 1
divisors.sort()

# primes and moebius
primes = []
mb = {}
x = n
id = 2
while id ** 2 <= x:
    if x % id == 0:
        primes.append(id)
        while x % id == 0:
            x //= id
    id += 1
if x > 1:
    primes.append(x)
x = len(primes)
for i in range(1 << x):
    mu = 1
    d = 1
    for j in range(x):
        if ((i >> j) & 1) == 1:
            mu *= -1
            d *= primes[j]
    mb[d] = mu

# cnt
cnt = {1:1}
for i in divisors:
    for p in primes:
        if i % p == 0:
            now = 1
            tmp = i
            while tmp % p == 0:
                now += 1
                tmp /= p
            cnt[i] = cnt[i/p] * now // (now - 1)
            break
res = 0
for nd in mb:
    d = n / nd
    u = mb[nd]
    c = cnt[d]
    res += (fact[c] * rfsum[c-1] * u % MOD + MOD) % MOD
    res %= MOD
print(res)