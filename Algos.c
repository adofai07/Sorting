// #include <bits/stdc++.h>
#include <stdio.h>
#include <iso646.h>
#include <malloc.h>
#include <time.h>

#include "xoshiro256starstar.h"

#define DATA_SIZE 100000000
#define DATA_MIN 0
#define DATA_MAX 1000000

// using namespace std;

int64_t arr[DATA_SIZE];

int CountingSort(int64_t *arr, int64_t data_size) {
    int64_t _min = 0;
    int64_t _max = 0;

    for (size_t i = 0; i < data_size; i++) {
        if (i == 0) {
            _min = arr[i];
            _max = arr[i];
        } else {
            if (arr[i] < _min) _min = arr[i];
            if (arr[i] > _max) _max = arr[i];
        }
    }

    size_t *cnt = (size_t *) malloc((_max - _min + 1) * sizeof(*cnt));

    // cout << "MIN = " << _min << ", MAX = " << _max << '\n';

    for (size_t i = 0; i < _max - _min + 1; i++) {
        cnt[i] = 0;
    }

    for (size_t i = 0; i < data_size; i++) {
        cnt[arr[i] - _min]++;
    }

    size_t idx = 0;

    for (size_t i = 0; i < _max - _min + 1; i++) {
        for (size_t j = 0; j < cnt[i]; j++) {
            arr[idx] = i + _min;
            idx++;
        }
    }

    // for (size_t i = 0; i < _max - _min + 1; i++) {
    //     cout << cnt[i] << ' ';
    // } cout << '\n';

    return 0;
}

int _MergeSort(int64_t *arr, size_t st, size_t ed) {

    if (st == ed) {
        return 0;
    } else if (st + 1 == ed) {
        if (arr[st] <= arr[ed]) {
            return 0;
        } else {
            arr[st] ^= arr[ed];
            arr[ed] ^= arr[st];
            arr[st] ^= arr[ed];
            return 0;
        }
    } else {
        size_t mid = (st + ed) / 2;

        _MergeSort(arr, st, mid);
        _MergeSort(arr, mid + 1, ed);

        size_t p1 = st;
        size_t p2 = mid + 1;

        while (p1 != mid and p2 != ed) {
            if (arr[p1] <= arr[p2]) {
                p1++;
            } else {
                arr[p1] ^= arr[p2];
                arr[p2] ^= arr[p1];
                arr[p1] ^= arr[p2];
                p2++;
            }
        }
        
        return 0;
    }

    return 0;
}

int MergeSort(int64_t *arr, int64_t data_size) {
    _MergeSort(arr, 0, data_size);

    return 0;
}

int main() {
    size_t TRIES = 5;
    set_seed();

    printf("Data size: %d, Data range: [%d, %d]\n", DATA_SIZE, DATA_MIN, DATA_MAX);

    while (TRIES--) {
        clock_t start_time, end_time;

        for (size_t i = 0; i < DATA_SIZE; i++) {
            arr[i] = next_r(DATA_MIN, DATA_MAX);
        }

        // for (size_t i = 0; i < DATA_SIZE; i++) {
        //     cout << arr[i] << ' ';
        // } cout << '\n';

        // Sorting fuction here
        start_time = clock();
        // CountingSort(arr, DATA_SIZE);
        MergeSort(arr, DATA_SIZE);
        end_time = clock();

        // for (size_t i = 0; i < DATA_SIZE; i++) {
        //     cout << arr[i] << ' ';
        // } cout << '\n';
        
        printf("Took time %.03lf\n", ((double) end_time - (double) start_time) / CLOCKS_PER_SEC);

    }

    // cin >> TRIES;

    return 0;
}