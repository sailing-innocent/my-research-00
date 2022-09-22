# Taichi

https://github.com/taichi-dev/taichi


taichi is a popular parallel programming library with a python interface. You can just use it similiar with other python libs but it is actually anther programming language that compile your code in the background to make it powerful.

## Why Taichi

### Taichi is Efficient

When calculating missions including much duplicated instructions, it si a good idea to make it computes parallel. However, the multi-thread and cuda is not that friendly.

```py
use_taichi = True

def is_prime(n: int):
    result = True 
    for k in range(2, int(n**0.5) + 1):
        if n%k == 0:
            result = False
            break
    return result;

def count_primes(n: int) -> int:
    count = 0
    for k in range(2, n):
        if is_prime(k):
            count += 1
        
    return count

if use_taichi:
    import taichi as ti
    ti.init()
    is_prime = ti.func(is_prime)
    count_primes = ti.kernel(count_primes)


import time

info = "use taichi" if use_taichi else "use python"
start = time.perf_counter()
print(count_primes(1000000))
print(f"time elapsed {info}: {time.perf_counter() - start} /s")

```

- IMG taichi-is-efficient.png

### Use Physics Simulation

