# Sorting

This project aims for developing a fast sorting algorithm for certain distributions.

## Outline

Compare-based sorting algorithms have a fundamental limit: their time complexity cannot go under $O(n \log{n})$. So, we combine them with other algorithms so that they can perform better.

## Method 1: *Merge Sort + Counting Sort*

The time complexity of the counting sort algorithm is $O(n + k)$, where $k$ is the range of data.

Given the data, we can establish a boundary condition for which algorithm will be faster:

$$an \log{n} = k + bn + c$$

Through several linear regressions, we found the coefficients $a$, $b$, and $c$ with $R^2 > 0.999$.

$$2.68 n \log{n} = k + 0.73n - 199$$

If $k < 2.68n \log⁡{n} - 0.73n + 199$ then the counting sort algorithm is faster, and otherwise the merge sort algorithm is faster.

We devided the data into $\sqrt{k}$ buckets, so that the $i$-th bucket would contain data in the range [$i \sqrt{k}$, $(i + 1) \sqrt{k}$]. Next, for each bucket, we figure out which sorting algorithm would be faster. After sorting each bucket, we merge the buckets using the Merge sort algorithm.

```diff
We omit the exact results.
```
