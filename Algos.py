from collections import defaultdict
from heapq import merge

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

def Timsort(array):
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

if __name__ == "__main__":
	from type import RandomizedListGenerator
	
	print(CountingSort(RandomizedListGenerator.Int.normal(1000, 0, 1)))