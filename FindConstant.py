from type import RandomizedListGenerator
from Algos import CountingSort, MergeSort, QuickSort, TimSort, RadixSort, FloatRadixSort
import time
import random
import statistics as stt
import sys
import os
import tqdm

"""
Counting Sort

RunningTime = O(n) + O(k) + O(1)

Merge Sort

RunningTime = O(n log n) + O(n) + O(logn) + O(1)

Quick Sort

RunningTime = O(n log n) + O(n) + O(logn) + O(1)

Tim Sort

RunningTime = O(n log n) + O(n) + O(logn) + O(1)

Radix Sort
"""

if __name__ == "__main__":
    T = time.time()
    N = 41
    
    F = [
        # MergeSort,
        # CountingSort,
        QuickSort,
        RadixSort,
        FloatRadixSort,
        TimSort,
    ]
    
    for f in tqdm.tqdm(F, position=0, leave=False):    
        # f = MergeSort
        
        dir_path = os.path.dirname(os.path.realpath(__file__))
        sys.stdout = open(FR"{dir_path}\Output-{f.__name__}-{N}.txt", "w+")

        N_K_LIST = [
            (i * 100000, j * 100000)
            for i in range(1, 11)
            for j in range(1, 11)
            for _ in range(N)
        ] + [
            (i * 10000, j * 10000)
            for i in range(1, 11)
            for j in range(1, 11)
            for _ in range(N)            
        ]
        
        random.shuffle(N_K_LIST)

        N_K_TIME_LIST = {}
        cnt = 0

        for (n, k) in tqdm.tqdm(N_K_LIST, position=1, leave=False):
            cnt += 1
            print(F"{cnt} / {200 * N}")
            print(F"{(n, k) = }")

            l = RandomizedListGenerator.Int.linear(n, 1, k)

            st = time.time()

            f(l)

            t = time.time() - st

            if F"{n}/{k}" in N_K_TIME_LIST:
                N_K_TIME_LIST[F"{n}/{k}"] += t
            
            else:
                N_K_TIME_LIST[F"{n}/{k}"] = t
                
            print(t)

        for i in range(1, 11):
            for j in range(1, 11):
                n = i * 10000
                m = j * 10000
                
                print(F"{n} {m} {N_K_TIME_LIST[F'{n}/{m}'] / N}")

        for i in range(1, 11):
            for j in range(1, 11):
                n = i * 100000
                m = j * 100000
                
                print(F"{n} {m} {N_K_TIME_LIST[F'{n}/{m}'] / N}")
                
        # print(N_K_TIME_LIST)
        print(F"Executed in {time.time() - T} seconds")