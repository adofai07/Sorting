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

if __name__ == "__main__":
	from type import RandomizedListGenerator
	
	print(CountingSort(RandomizedListGenerator.Int.normal(1000, 0, 1)))