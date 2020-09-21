n,m = map(int,input().split())
rg = [[0] * 0 for _ in range(n)]
reachable = [False] * n
for i in range(m):
    a,b = map(int,input().split())
    a -= 1
    b -= 1
    rg[b].append(a)

def update(x):
    if reachable[x]:
        return
    reachable[x] = True
    st = [x]
    while len(st) > 0:
        now = st.pop()
        for to in rg[now]:
            if not reachable[to]:
                reachable[to] = True
                st.append(to)

update(0)
q = int(input())
for _ in range(q):
    x,y = map(int,input().split())
    y -= 1
    if x == 2:
        if reachable[y]:
            print("YES")
        else:
            print("NO")
    else:
        update(y)