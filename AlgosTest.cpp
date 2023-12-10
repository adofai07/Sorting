#include <bits/stdc++.h>
#include "xoshiro256starstar.h"

#define DATA_SIZE 10
#define DATA_MIN 0
#define DATA_MAX 1000000

using namespace std;

int64_t arr[DATA_SIZE];


int InsertionSort(int64_t *arr, int st, int ed);

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

    free(cnt);

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
    } else if (st + 16 > ed) {
        InsertionSort(arr, st, ed);
        return 0;
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

int QuickSort(int64_t *arr, int64_t data_size) {
    if (data_size < 2) return 0;

    int64_t pivot = arr[data_size / 2];
    int64_t i, j;

    for (i = 0, j = data_size - 1; ; i++, j--) {
        while (arr[i] < pivot) { i++; }
        while (arr[j] > pivot) { j--; }

        if (i >= j) {
            break;
        }

        arr[i] ^= arr[j];
        arr[j] ^= arr[i];
        arr[i] ^= arr[j];
    }

    QuickSort(arr, i);
    QuickSort(arr + i, data_size - i);

    return 0;
}

int RandomizedQuickSort(int64_t *arr, int64_t data_size) {
    if (data_size < 2) return 0;

    int64_t pivot = arr[next_r(0, data_size)];
    int64_t i, j;

    for (i = 0, j = data_size - 1; ; i++, j--) {
        while (arr[i] < pivot) { i++; }
        while (arr[j] > pivot) { j--; }

        if (i >= j) {
            break;
        }

        arr[i] ^= arr[j];
        arr[j] ^= arr[i];
        arr[i] ^= arr[j];
    }

    RandomizedQuickSort(arr, i);
    RandomizedQuickSort(arr + i, data_size - i);

    return 0;
}

int _RadixSort(int64_t *arr, int st, int ed) {
    const int r = 16;

    int64_t _min = 0;
    int64_t _max = 0;
    for (int i = st; i < ed; i++) {
        if (i == 0) {
            _min = arr[i];
            _max = arr[i];
        } else {
            if (arr[i] < _min) _min = arr[i];
            if (arr[i] > _max) _max = arr[i];
        }
    }

    if (_max == _min) return 0;

    for (int i = st; i < ed; i++) arr[i] -= _min;

    double d = log(_max - _min)/log(r);

    for (int i = 0; i <= d; i++) {
        vector<int> cnt[r], res;
        for (int j = st; j < ed; j++) {
            int64_t t = (arr[j] % (int64_t)pow(r, i+1)) / (int64_t)pow(r, i);
            cnt[t].push_back(j);
        }
        for (int k = 0; k < r; k++) {
            for (int j = 0; j < (int)cnt[k].size(); j++)
                res.push_back(arr[cnt[k][j]]);
        }
        for (int j = st; j < ed; j++) arr[j] = res[j - st];
    }

    for (int i = st; i < ed; i++) arr[i] += _min;

    return 0;
}

int RadixSort(int64_t *arr, int64_t data_size) {
    _RadixSort(arr, 0, data_size);

    return 0;
}

int find_minrun(int data_size) {
    int r = 0;
    while (data_size >= 32) {
        r |= data_size bitand 1;
        data_size >>= 1;
    }
    return data_size + r;
}

int InsertionSort(int64_t *arr, int st, int ed) {
    for (int i = st; i < ed; i++) {
        int64_t now = arr[i];
        int j = i - 1;
        while ((int)j >= (int)st and now < arr[j]) {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = now;
    }

    return 0;
}

int _merge(int64_t *arr, int lt, int mid, int rt) {

    vector<int> temp;
    int p = lt, q = mid;

    while (true) {
        if (p >= mid and q >= rt) break;
        if (p >= mid) {
            temp.push_back(arr[q]);
            q++;
            continue;
        }
        if (q >= rt) {
            temp.push_back(arr[p]);
            p++;
            continue;
        }
        if (arr[p] <= arr[q]) {
            temp.push_back(arr[p]);
            p++;
        }
        else {
            temp.push_back(arr[q]);
            q++;
        }
    }

    for (int i = lt; i < rt; i++) arr[i] = temp[i - lt];

    return 0;
}

int TimSort(int64_t *arr, int64_t data_size) {
    int minrun = find_minrun(data_size);

    for (int st = 0; st < data_size; st += minrun) {
        int ed = min(st + minrun, (int)data_size);
        InsertionSort(arr, st, ed);
    }

    int sz = minrun;
    while (sz < data_size) {
        for (int lt = 0; lt < data_size; lt += minrun * 2) {
            int mid = min((int)data_size, lt + sz);
            int rt = min(lt + 2 * sz, (int)data_size);
            _merge(arr, lt, mid, rt);
        }
        sz *= 2;
    }

    return 0;
}

int main() {
    size_t TRIES = 1;
    set_seed();

    printf("Data size: %d, Data range: [%d, %d]\n", DATA_SIZE, DATA_MIN, DATA_MAX);

    while (TRIES--) {
        clock_t start_time, end_time;

        for (size_t i = 0; i < DATA_SIZE; i++) {
            arr[i] = next_r(DATA_MIN, DATA_MAX);
        }

        for (size_t i = 0; i < DATA_SIZE; i++) {
            cout << arr[i] << ' ';
        } cout << '\n';

        // Sorting fuction here
        start_time = clock();
        // CountingSort(arr, DATA_SIZE);
        MergeSort(arr, DATA_SIZE);
        // QuickSort(arr, DATA_SIZE);
        // RandomizedQuickSort(arr, DATA_SIZE);
        // RadixSort(arr, DATA_SIZE);
        // TimSort(arr, DATA_SIZE);
        end_time = clock();

        for (size_t i = 0; i < DATA_SIZE; i++) {
            cout << arr[i] << ' ';
        } cout << '\n';
        
        printf("Took time %.03lf\n", ((double) end_time - (double) start_time) / CLOCKS_PER_SEC);

    }

    // cin >> TRIES;

    return 0;
}