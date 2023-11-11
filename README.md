# Sorting

This project aims for developing a fast sorting algorithm for certain distributions.

## Outline

Compare-based sorting algorithms have a fundamental limit: their time complexity cannot go under $O(n \log{n})$. So, we combine them with other algorithms so that they can perform better.

## Method 1: *Merge Sort + Counting Sort*

The time complexity of the counting sort algorithm is $O(n + k)$, where $k$ is the range of data.

Given the data, we can establish a boundary condition for which algorithm will be faster:

$$\large an \log{n} = k + bn + c$$

Through several linear regressions, we found the coefficients $a$, $b$, and $c$ with $R^2 > 0.999$.

$$\large 2.68 n \log{n} = k + 0.73n - 199$$

If $k < 2.68n \log⁡{n} - 0.73n + 199$ then the counting sort algorithm is faster, and otherwise the merge sort algorithm is faster.

We devided the data into $\sqrt{k}$ buckets, so that the $i$-th bucket would contain data in the range $[i \sqrt{k}, (i + 1) \sqrt{k}]$. Next, for each bucket, we figure out which sorting algorithm would be faster. After sorting each bucket, we merge the buckets using the Merge sort algorithm.

```diff
We omit the exact results.
```

## Method 2: *Quick Sort + Counting Sort*

(Update needed)
We thought the merge sort algorithm might be too slow, so we are going to use one of the two algorithms:

* Quick Sort
* RandQS

The **RandQS** algorithm guarantees a time complexity of $O(n \log{n})$ whereas the classical quick sort algorithm doesn't.

## Method 3: *Quick Sort/Merge Sort + Radix Sort*

(Update needed)
We thought we should be able to sort non-integer types of data, so we decided to use the radix sort algorithm. Although it might be a little slow, it is definitely worth to try.

## Method 4: *Neural network + Insertion Sort*

(Update needed)
This is a completely new approach using neural networks. Given the distribution family, we extract $\sqrt{n}$ data and get the mean and standard deviation(stdev). Then we enter the three values *mean*, *stdev*, and *an element in the list*. The neural network gives an estimate of the index of the element in a fully sorted list. Eventually, we get an almost sorted list.

Then we sort the *almost sorted list* with the insertion sort algorithm.
