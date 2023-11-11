# Sorting

This project aims for developing a fast sorting algorithm for certain distributions.

## Outline

Compare-based sorting algorithms have a fundamental limit: their time complexity cannot go under $\displaystyle O(n \log{n})$. So, we combine them with other algorithms so that they can perform better.

## Method 1: *Merge Sort + Counting Sort*

The time complexity of the counting sort algorithm is $\displaystyle O(n + k)$, where $\displaystyle k$ is the range of data.

Given the data, we can establish a boundary condition for which algorithm will be faster:

$$
\displaystyle

\begin{equation}
    an \log{n} = k + bn + c
\end{equation}
$$

Through several linear regressions, we found the coefficients $\displaystyle a$, $\displaystyle b$, and $\displaystyle c$ with $\displaystyle R^2 > 0.999$.

$$
\displaystyle

\begin{equation}
    2.68 n \log{n} = k + 0.73n - 199
\end{equation}
$$

If $\displaystyle k < 2.68n \log⁡{n} - 0.73n + 199$ then the counting sort algorithm is faster, and otherwise the merge sort algorithm is faster.

We devided the data into $\displaystyle \sqrt{k}$ buckets, so that the $\displaystyle i$-th bucket would contain data in the range [$\displaystyle i \sqrt{k}$, $\displaystyle (i + 1) \sqrt{k}$]. Next, for each bucket, we figure out which sorting algorithm would be faster. After sorting each bucket, we merge the buckets using the Merge sort algorithm.

```diff
We omit the exact results.
```
