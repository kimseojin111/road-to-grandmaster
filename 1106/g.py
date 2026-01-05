

def is_prime(x):
    if x < 2:
        return False
    for d in range(2, int(x**0.5)+1):
        if x % d == 0:
            return False
    return True

def goldbach_pairs(n):
    r = []
    for i in range(2, n//2 + 1):
        if is_prime(i) and is_prime(n - i):
            r.append((i, n - i))
    return r

n = 24
result = goldbach_pairs(n)
print(result)
print(len(result))