#include <bits/stdc++.h>
#include <windows.h>
#include "xoshiro256starstar.h"

#define DATA_SIZE 100000000
#define DATA_MIN 0
#define DATA_MAX 1000000

using namespace std;

typedef int (*sortfn_t)(int64_t *, int64_t);

int64_t arr[DATA_SIZE];

static inline int64_t GetTicks(void)
{
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
    // printf("%p\n", cnt);

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
    size_t TRIES = 2;
    set_seed();
    sortfn_t x[] = {CountingSort, MergeSort};

    vector<int64_t> N_LIST;
    vector<int64_t> K_LIST;

    // printf("Data size: %d, Data range: [%d, %d]\n", DATA_SIZE, DATA_MIN, DATA_MAX);

    for (int i = 4; i < 7; i++) {
        for (int j = 1; j < 10; j++) {
            int64_t arr_len = pow(10, i) * j;
            // int64_t *arr = (int64_t *) malloc(sizeof(*arr) * arr_len);

            int64_t k1 = 0, k2 = 4000000000LL, mid_k;

            while (k1 + 6 < k2) {
                mid_k = (k1 + k2) / 2;

                int64_t start_time1, end_time1, start_time2, end_time2;
                int64_t t1 = 0, t2 = 0;

                for (int t = 0; t < TRIES; t++) {
                    for (int k = 0; k < arr_len; k++) {
                        arr[k] = next_r(0, mid_k);
                    }

                    start_time1 = GetTicks();
                    (x[0])(arr, arr_len);
                    end_time1 = GetTicks() - start_time1;

                    t1 += end_time1;

                    for (int k = 0; k < arr_len; k++) {
                        arr[k] = next_r(0, mid_k);
                    }

                    start_time2 = GetTicks();
                    (x[1])(arr, arr_len);
                    end_time2 = GetTicks() - start_time2;

                    t2 += end_time2;

                    for (int k = 0; k < arr_len; k++) {
                        arr[k] = next_r(0, mid_k);
                    }

                    start_time2 = GetTicks();
                    (x[1])(arr, arr_len);
                    end_time2 = GetTicks() - start_time2;

                    t2 += end_time2;
                    
                    for (int k = 0; k < arr_len; k++) {
                        arr[k] = next_r(0, mid_k);
                    }

                    start_time1 = GetTicks();
                    (x[0])(arr, arr_len);
                    end_time1 = GetTicks() - start_time1;

                    t1 += end_time1;
                }

                printf("N: %de%d, Range of K: [%lld, %lld], f1: %lld ticks, f2: %lld ticks               \r", j, i, k1, k2, t1, t2);

                if (t1 < t2) {
                    k1 = mid_k;
                } else {
                    k2 = mid_k;
                }
            }

            printf("\n");

            N_LIST.push_back(arr_len);
            K_LIST.push_back((k1 + k2) / 2);
        }
    }

    printf("----------%d RESULTS----------\n", N_LIST.size());

    for (int i = 0; i < N_LIST.size(); i++) {
        printf("%lld %lld\n", N_LIST[i], K_LIST[i]);
    }

    // while (--TRIES) {
    //     clock_t start_time, end_time;

    //     for (size_t i = 0; i < DATA_SIZE; i++) {
    //         arr[i] = next_r(DATA_MIN, DATA_MAX);
    //     }

    //     // for (size_t i = 0; i < DATA_SIZE; i++) {
    //     //     cout << arr[i] << ' ';
    //     // } cout << '\n';

    //     // Sorting fuction here
    //     start_time = GetTicks();
    //     // CountingSort(arr, DATA_SIZE);
    //     MergeSort(arr, DATA_SIZE);
    //     end_time = GetTicks();

    //     // for (size_t i = 0; i < DATA_SIZE; i++) {
    //     //     cout << arr[i] << ' ';
    //     // } cout << '\n';
        
    //     printf("Took time %.03lf\n", ((double) end_time - (double) start_time) / CLOCKS_PER_SEC);

    // }

    return 0;
}