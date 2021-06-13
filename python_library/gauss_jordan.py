class bit_matrix:
    def __init__(self, h, w):
        self.h = h
        self.w = w
        self.m = [0] * h

    def setval(self, row, col, val):
        self.m[row] ^= self.m[row] & (1 << col)
        self.m[row] |= val << col

    def print_mat(self):
        print("---")
        print("h:", self.h, "w:", self.w)
        for i in range(self.h):
            print("".join(list(reversed((bin(self.m[i])[2:]).zfill(self.w)))))
        print("---")


def gauss_jordan(bm, is_extended):
    rank = 0
    for col in range(bm.w):
        if is_extended and col == bm.w:
            break
        piv = -1
        for row in range(rank, bm.h):
            if bm.m[row] >> col & 1:
                piv = row
                break
        if piv == -1:
            continue
        bm.m[piv], bm.m[rank] = bm.m[rank], bm.m[piv]
        for row in range(bm.h):
            if row != rank and (bm.m[row] >> col & 1):
                bm.m[row] ^= bm.m[rank]
        rank += 1
    return (rank, bm)


def linear_equation(bm, b):
    h = bm.h
    w = bm.w
    mat = bit_matrix(h, w + 1)
    for i in range(h):
        mat.m[i] = bm.m[i] | b[i] << w
    rank, mat = gauss_jordan(mat, True)
    for row in range(rank, h):
        if mat.m[row] >> w & 1:
            return (-1, [-1] * w)
    res = [0] * w
    for i in range(rank):
        res[i] = mat.m[i] >> w & 1
    return (rank, res)