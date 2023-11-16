import time
from type import RandomizedListGenerator
from Algos import *

def FasterSort(N: int, K: int, f1: callable, f2: callable) -> callable:
    t1, t2 = 0, 0

    for _ in range(500):
        L = RandomizedListGenerator.Int.linear(N, 0, K)

        st = time.time()
        f1(L)
        t1 += time.time() - st

        st = time.time()
        f2(L)
        t2 += time.time() - st
        
        L = RandomizedListGenerator.Int.linear(N, 0, K)

        st = time.time()
        f2(L)
        t2 += time.time() - st

        st = time.time()
        f1(L)
        t1 += time.time() - st

    if t1 < t2: return f1
    else: return f2

def find_K_for_N(N: int, f1: callable, f2: callable) -> int:
    K_range = [1, N ** 2 // 10]

    if FasterSort(N, 1, f1, f2) == f2:
        f1, f2 = f2, f1
    
    while True:
        mid_K = sum(K_range) // 2

        if FasterSort(N, mid_K, f1, f2) == f1:
            K_range[0] = mid_K

        else:
            K_range[1] = mid_K

        if K_range[1] - K_range[0] < 5:
            return sum(K_range) // 2
        
        print(f1.__name__, f2.__name__, N, K_range)
        
def find_boundaries(f1: callable, f2: callable):
    N_list = [
        100, 200, 300, 400, 500, 600, 700, 800, 900,
        1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
    ]

    K_list = [find_K_for_N(i, f1, f2) for i in N_list]

    return (N_list, K_list)

if __name__ == "__main__":
    print(find_K_for_N(1000, CountingSort, QuickSort))