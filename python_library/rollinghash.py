class rollinghash:
    def __init__(self, base, s):
        self.n = len(s)
        self.MOD = 10**9 + 7
        self.hash = [0] * (self.n + 1)
        self.pow = [1] * (self.n + 1)
        self.base = base
        for i, c in enumerate(s):
            self.hash[i+1] = (self.hash[i] * base + ord(c)) % self.MOD
            self.pow[i+1] = self.pow[i] * base % self.MOD

    def add(self, c):
        self.n += 1
        self.hash.append((self.hash[-1] * self.base + ord(c)) % self.MOD)
        self.pow.append(self.pow[-1] * self.base % self.MOD)

    def pop(self):
        self.n -= 1
        self.hash.pop(-1)
        self.pow.pop(-1)

    def calc(self, l, r):
        return (self.hash[r]-self.hash[l]*self.pow[r-l] % self.MOD) % self.MOD
