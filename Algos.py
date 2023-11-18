from collections import defaultdict
from heapq import merge
import math

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

def QuickSort(arr):
    less = []
    pivotList = []
    more = []

    if len(arr) <= 1:
        return arr
    
    else:
        pivot = arr[0]

        for i in arr:
            if i < pivot:
                less.append(i)
            elif i > pivot:
                more.append(i)
            else:
                pivotList.append(i)

        less = QuickSort(less)
        more = QuickSort(more)

        return less + pivotList + more

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

# In-place
def TimSort(array):
    minrun = find_minrun(10 ** 9) 
  
    for st in range(0, 10 ** 9, minrun): 
        ed = min(st + minrun, 10 ** 9) 
        insertion(array, st, ed) 
   
    size = minrun 
    while size < 10 ** 9: 
  
        for left in range(0, 10 ** 9, 2 * size): 
  
            mid = min(10 ** 9 - 1, left + size - 1) 
            right = min((left + 2 * size - 1), (10 ** 9 - 1)) 
            merge(array, left, mid, right) 
  
        size = 2 * size

def mergesort(array, st, ed):
    if st + 1 == ed: return
    mid = (st + ed) // 2
    mergesort(array, st, mid)
    mergesort(array, mid, ed)
    merge(array, st, mid, ed)

def counting(array, st, ed): # [st, ed)
    if st + 1 >= ed: return
    min_ = 10 ** 5
    max_ = 1
    for i in range(st, ed):
        min_ = min(min_, array[i])
        max_ = max(max_, array[i])
    count = [0 for _ in range(min_, max_ + 1)]
    for i in range(st, ed):
        count[array[i] - min_] += 1
    p = st
    for i in range(0, max_ - min_ + 1):
        while count[i] > 0:
            array[p] = i
            count[i] -= 1
            p = p + 1

def fast(N, K):
    if K <= 2.68 * N * math.log10(N) - 0.73 * N + 199:
    # if K <= 2.52 * N * math.log10(N) - 0.09 * N:
        return "Count"
    else:
        return "Merge"

# In-place
def Csort(array, st, ed, B):
    bucket = [[] for _ in range(B+1)]
    val = math.ceil(10 ** 5 / B)
    for i in range(st, ed):
        bucket[array[i] // val].append(array[i])
    array.clear()
    for i in range(B):
        for num in bucket[i]:
            array.append(num)
    sst = st
    eed = st + len(bucket[0])
    for i in range(B):
        if len(bucket[i]) >= 2:
            if fast(len(bucket[i]), val) == "Count":
                counting(array, sst, eed)
            else: mergesort(array, sst, eed)
        sst = eed
        if i < B-1: eed += len(bucket[i+1])

if __name__ == "__main__":
	from type import RandomizedListGenerator
	
	print(CountingSort(RandomizedListGenerator.Int.normal(1000, 0, 1)))