#include <bits/stdc++.h>
#include <windows.h>
#include "xoshiro256starstar.h"
#include "Algos.hpp"

#define DATA_SIZE 10
#define DATA_MIN 0
#define DATA_MAX 100000
#define ARR_LEN(x) (sizeof(x) / sizeof(*x))

typedef int (*sortfn_t)(int64_t *, int64_t);

using namespace std;

int64_t arr[DATA_SIZE];

sortfn_t FasterSort(int64_t data_size, int64_t data_range) {
    if (data_range < 0.771369737421915 * data_size * log(data_size) + 8.54667506418645 * n)
    return true;
}

int OutMethod3(int64_t *arr, int64_t data_size) {
    int64_t _min = 0;
    int64_t _max = 0;

    for (int i = 0; i < data_size; i++) {
        if (i == 0) {
            _min = arr[i];
            _max = arr[i];
        } else {
            if (arr[i] < _min) { _min = arr[i]; }
            if (arr[i] > _max) { _max = arr[i]; }
        }
    }

    for (int i = 0; i < data_size; i++) { arr[i] -= _min; }

    int b = min(data_size, (int64_t)sqrt(_max - _min));
    vector<int64_t> bucket[b];

    int64_t val = ceil((_max - _min + 1) / (double)b);

    for (int i = 0; i < data_size; i++) {
        bucket[arr[i] / val].push_back(arr[i]);
    }

    int r = -1;

    for (int i = 0; i < b; i++) {
        for (int j = 0; j < bucket[i].size(); j++) {
            arr[++r] = bucket[i][j];
        }
    }

    int st = 0;
    int ed = st + bucket[0].size();
    
    for (int i = 0; i < b; i++) {
        if (bucket[i].size() >= 2) {
            if (FasterSort(bucket[i].size(), val)) {
                _RadixSort(arr, st, ed);
            }
            else {
                _MergeSort(arr, st, ed);
            }
        }

        st = ed;
        if (i < b - 1) { ed += bucket[i + 1].size(); }
    }

    for (int i = 0; i < data_size; i++) { arr[i] += _min; }

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    for (int i = 0; i < DATA_SIZE; i++) {
        arr[i] = next_r(DATA_MIN, DATA_MAX);
    }

    vector<sortfn_t> F;
    F.push_back(OutMethod3)

    cout << GetFreq() << '\n';
}