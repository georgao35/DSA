import random

# 3 组数据，每个数不超过 10 位
n = 3
hi = 10 ** 10

print(n)
for _ in range(n):
    a = random.randrange(0, hi)  # randrange 不包含 hi
    b = random.randrange(0, hi)
    print(a, b)
