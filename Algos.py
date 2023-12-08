from collections import defaultdict
from heapq import merge
import math
import time
import tqdm
from type import RandomizedListGenerator
import sys

sys.setrecursionlimit(2147483647)
n = 10 ** 5

def _CountingSort(array, mn, mx):
	count = defaultdict(int)
	
	for i in array:
		count[i] += 1
		
	result = []
	
	for j in range(mn, mx + 1):
		result += [j] * count[j]
		
	return result

def CountingSort(arr):
	return _CountingSort(arr, min(arr), max(arr))

def _QuickSort(arr, st, ed):
    less = []
    pivotList = []
    more = []

    if ed - st <= 1:
        return
    
    else:
        pivot = arr[st]

        for i in range(st, ed):
            if arr[i] < pivot:
                less.append(arr[i])
            elif arr[i] > pivot:
                more.append(arr[i])
            else:
                pivotList.append(arr[i])

        p = st
        for val in less:
            arr[p] = val
            p += 1
        _QuickSort(arr, st, p)
        for val in pivotList:
            arr[p] = val
            p += 1
        q = p
        for val in more:
            arr[p] = val
            p += 1
        _QuickSort(arr, q, ed)

def QuickSort(arr):
	return _QuickSort(arr, 0, len(arr))


def MergeSort(m):
    if len(m) <= 1:
        return m

    middle = len(m) // 2
    left = m[:middle]
    right = m[middle:]

    left = MergeSort(left)
    right = MergeSort(right)

    return list(merge(left, right))

def find_minrun(n):
    r = 0
    while n >= 32: 
        r |= n & 1
        n >>= 1
    return n + r

def insertion(array, st, ed): 
    for i in range(st + 1, ed):
        element = array[i]
        j = i - 1
        while element < array[j] and j >= st:
            array[j + 1] = array[j]
            j -= 1
        array[j + 1] = element
    return array

def TimSort(array):
    minrun = find_minrun(n) 
  
    for st in range(0, n, minrun): 
        ed = min(st + minrun, n) 
        insertion(array, st, ed) 
   
    size = minrun 
    while size < n: 
  
        for left in range(0, n, 2 * size): 
  
            mid = min(n - 1, left + size - 1) 
            right = min((left + 2 * size - 1), (n - 1)) 
            array[left:right] = list(merge(array[left:mid], array[mid:right]) )
  
        size = 2 * size

def mergesort(array, st, ed):
    if st + 1 == ed: return
    mid = (st + ed) // 2
    mergesort(array, st, mid)
    mergesort(array, mid, ed)
    merge(array, st, mid, ed)

def counting(array, st, ed): # [st, ed)
    if st + 1 >= ed: return
    min_ = min(array[st:ed])
    max_ = max(array[st:ed])
    count = [0 for _ in range(min_, max_ + 1)]
    for i in range(st, ed):
        count[array[i] - min_] += 1
    p = st
    for i in range(0, max_ - min_ + 1):
        while count[i] > 0:
            array[p] = i
            count[i] -= 1
            p = p + 1

def RadixSort(arr):
    r = 16
    n = len(arr)
    min_ = min(arr)
    max_ = max(arr)
    if min_ == max_: return
    d = math.log(max_ - min_) / math.log(r)
    for i in range(int(d) + 1):
        cnt = [[] for _ in range(r)]
        res = []
        for j in range(n):
            t = ((arr[j] - min_) >> (4*i)) & (r-1)
            cnt[t].append(j)
        for m in range(r):
            for j in range(len(cnt[m])):
                res.append(arr[cnt[m][j]])
        arr = res[:]

def RadixIndex(arr, manti):
    r = 16
    n = len(arr)
    min_ = min(manti)
    max_ = max(manti)
    if min_ == max_: return arr
    d = math.log(max_ - min_) / math.log(r)
    for i in range(int(d) + 1):
        cnt = [[] for _ in range(r)]
        cnt2 = [[] for _ in range(r)]
        res = []
        res2 = []
        for j in range(n):
            t = ((manti[j] - min_) >> (4*i)) & (r-1)
            cnt[t].append(arr[j])
            cnt2[t].append(manti[j])
        for m in range(r):
            for j in range(len(cnt[m])):
                res.append(cnt[m][j])
            for j in range(len(cnt2[m])):
                res2.append(cnt2[m][j])
        arr = res[:]
        manti = res2[:]
    return arr

# 64bit IEEE 754 standard floating-point arithmetic
def FloatRadixSort(arr):
    n = len(arr)
    min_ = min(arr)
    max_ = max(arr)

    expon = arr[:]
    manti = arr[:]
    for i in range(len(arr)):
        e = math.floor(math.log2(arr[i] - min_ + 1))
        m = int((arr[i] - min_ + 1) / (2**e) * (2**52))
        expon[i] = e
        manti[i] = m

    d = max(expon)
    cnt = [[] for _ in range(d + 1)]
    res = []
    for j in range(n):
        cnt[expon[j]].append(j)
    for m in range(d + 1):
        if len(cnt[m]) == 0: continue
        part = []
        for j in range(len(cnt[m])):
            part.append(manti[cnt[m][j]])
        cnt[m] = RadixIndex(cnt[m], part)
        for j in range(len(cnt[m])):
            res.append(arr[cnt[m][j]])
    arr = res[:]

if __name__ == "__main__":
	from type import RandomizedListGenerator
	
	print(CountingSort(RandomizedListGenerator.Int.normal(1000, 0, 1)))