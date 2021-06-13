def extgcd(a, b):
    s = 1
    t = 0
    u = 0
    v = 1
    while b != 0:
        tmp = a // b
        a = a - b * tmp
        s = s - u * tmp
        t = t - v * tmp
        s, u = u, s
        t, v = v, t
        a, b = b, a
    return [s, t, a]


def calc_inv(n, mod):
    res = extgcd(n, mod)
    return (res[0] + mod) % mod
