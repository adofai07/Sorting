#ifndef ALGOS_H
#define ALGOS_H

#include <stdint.h>

int64_t GetTicks(void);
int64_t GetFreq(void);
int CountingSort(int64_t *arr, int64_t data_size);
int MergeSort(int64_t *arr, int64_t data_size);
int QuickSort(int64_t *arr, int64_t data_size);
int RandomizedQuickSort(int64_t *arr, int64_t data_size);
int RadixSort(int64_t *arr, int64_t data_size);
int TimSort(int64_t *arr, int64_t data_size);
int InsertionSort(int64_t *arr, int st, int ed);

#endif