import random

Y = 500
print(Y)

for _ in range(Y):
    L = 10**18
    N = 10000
    M = random.randint(1, N)     # any M ≤ N
    s = random.randint(1, 10**12) # seed
    P = random.randint(1, 10**9)  # positive integer
    print(L, N, M, s, P)
