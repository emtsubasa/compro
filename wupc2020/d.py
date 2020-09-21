def extgcd(a,b):
    s = 1
    t = 0
    u = 0
    v = 1
    while b != 0:
    	tmp = a // b
    	a = a - b * tmp
    	s = s - u * tmp
    	t = t - v * tmp
    	s,u = u,s
    	t,v = v,t
    	a,b = b,a
    return [s,t,a]

def calc_inv(p,mod):
    res = extgcd(p,mod)
    return (res[0] + mod) % mod

n,m,q = map(int,input().split())
d = list(map(int,input().split()))
al = 1
for i in range(m):
    d[i] = calc_inv(d[i],n)
    al = al * d[i] % n
mul = [1] * (2 * m + 1)
for i in range(2*m):
    mul[i+1] = mul[i] * d[i%m] % n
for i in range(q):
    x,y,z = map(int,input().split())
    y -= 1
    e = pow(al,z // m,n) * mul[y + z % m] * calc_inv(mul[y],n) % n
    print(pow(x,e,n+1))