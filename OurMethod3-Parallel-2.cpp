#include <bits/stdc++.h>
#include <windows.h>
#include "xoshiro256starstar.h"
#include <omp.h>

#define DATA_SIZE 10
#define DATA_MIN 0
#define DATA_MAX 100000
#define ARR_LEN(x) (sizeof(x) / sizeof(*x))
#define MAX_THREADS 8

typedef int (*sortfn_t)(int64_t *, int64_t);

using namespace std;

int InsertionSort(int64_t *arr, int st, int ed);

int64_t GetFreq(void) {
    LARGE_INTEGER freq;

    if (!QueryPerformanceFrequency(&freq))
        return 0;
    
    return freq.QuadPart;
}

int64_t GetTicks(void) {
    LARGE_INTEGER ticks;

    if (!QueryPerformanceCounter(&ticks))
        return 0;

    return ticks.QuadPart;
}


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

int FormatNumber(int64_t n) {
    for (int i = 0; ; i++, n /= 10) {
        if (n == 1) {
            return i;
        }
    }
}

bool fast(int64_t data_size, int64_t data_range) {
    if (data_range < 1.70928784082079 * data_size * log(data_size) + 5.3980026568648 * data_size + 1688073.6770364) {
        return true;
    } else {
        return false;
    }

    return true;
}

int Csort(int64_t *arr, int64_t data_size) {

    int64_t _min = 0;
    int64_t _max = 0;

    for (int i = 0; i < data_size; i++) {
        if (i == 0) {
            _min = arr[i];
            _max = arr[i];
        } else {
            if (arr[i] < _min) _min = arr[i];
            if (arr[i] > _max) _max = arr[i];
        }
    }

    #pragma omp parallel for
        for (int i = 0; i < data_size; i++) arr[i] -= _min;

    // printf("[01]> ");

    // int b = min(data_size, (int64_t)(sqrt(_max - _min) * 0.06)) + 1;
    int b = (int) (pow(data_size, 0.5) * (pow(_max - _min, 0.4) * 0.0001)) + 1;
    
    int64_t *out = (int64_t *) malloc(sizeof(*out) * data_size);
    int64_t *inds = (int64_t *) calloc(b + 1, sizeof(*inds));

    // printf("[02]> ");

    int64_t val = ceil((_max - _min + 1) / (double)b);

    /* count numbers for each bin */
    #pragma omp parallel for
        for (int i = 0; i < data_size; i++) {
            #pragma omp atomic
            inds[(arr[i] / val) + 1]++;
        }

    /* cumulatively sum */
    for (int i = 1; i < b; i++)
        inds[i] += inds[i - 1];

    /* store the data */
    for (int i = 0; i < data_size; i++) {
        out[inds[arr[i] / val]] = arr[i];
        inds[arr[i] / val]++;
    }


    #pragma omp parallel for
        for (int i = 0; i < b; i++) {
            const int prev = (i == 0 ? 0 : inds[i - 1]);
            const int bucket_n = inds[i] - prev;
            if (fast(bucket_n, val)) {
                // _RadixSort(arr, st, ed);
                CountingSort(out + prev, bucket_n);
            } else {
                // _MergeSort(arr, st, ed);
                QuickSort(out + prev, bucket_n);
            }
        }

    printf("B%d ", b);

    #pragma omp parallel for
        for (int i = 0; i < data_size; i++) {
            arr[i] = (out[i] + _min);
        }

    free(out);
    free(inds);

    return 0;
}

int64_t arr[100000100];

int main() {
    // ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    set_seed();
    omp_set_num_threads(MAX_THREADS);

    int64_t TRIES = 10;

    int64_t start_ticks, end_ticks;
    sortfn_t F[4] = {Csort, CountingSort, MergeSort, QuickSort};
    double times[4] = { 0.0, 0.0, 0.0, 0.0 };

    for (int i = 7; i < 9; i++) for (int j = 8; j < 10; j++) {
        int64_t n = pow(10, i);
        int64_t k = pow(10, j);

        times[0] = 0.0;
        times[1] = 0.0;
        times[2] = 0.0;
        times[3] = 0.0;
        // printf("%lld %lld ", n, k);

        for (int t = 1; t <= TRIES; t++) {
            printf("(%03d / %03d) 1e%d 1e%d ", t, TRIES, FormatNumber(n), FormatNumber(k));

            for (int f = 0; f < 4; f++) {
                // int64_t arr[n];

                for (int j = 0; j < n; j++) {
                    arr[j] = next_r(0, k);
                }

                // printf("[05]> ");

                start_ticks = GetTicks();
                F[f](arr, n);
                end_ticks = GetTicks();

                times[f] += (double) (end_ticks - start_ticks) / GetFreq();

                printf("%.03lf ", times[f] / t);
            }
            printf("\r");
        }
        printf("\n");
    }
}