#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "xoshiro256starstar.h"
#include <time.h>

#define DATA_SIZE 100000000
#define DATA_MIN 0
#define DATA_MAX 16000

const int data_size = DATA_SIZE;
const int data_min = DATA_MIN;
const int data_max = DATA_MAX;

int64_t aaa[DATA_SIZE];

int CountingSort(int64_t *data, int64_t a, int64_t b, size_t len);

int main(void)
{
    set_seed();

    clock_t start, end;

    for (size_t i = 0; i < data_size; i++)
        aaa[i] = next_r(data_min, data_max);

    start = clock();
    CountingSort(aaa, data_min, data_max, data_size);
    end = clock();

    printf("Took time %lf\n", ((double) end - (double) start) / CLOCKS_PER_SEC);

    return 0;
}

int CountingSort(int64_t *data, int64_t a, int64_t b, size_t len)
{
    if (b < a)
        return 2;

    size_t *count = malloc((b - a + 1) * sizeof(*count));
    int64_t ind;

    if (!count)
        return 1;

    for (size_t i = 0; i < len; i++) {
        ind = data[i];

        if (ind < a)
            ind = a;
        if (ind > b)
            ind = b;

        count[ind - a]++;
    }

    size_t *d_i = count;

    for (size_t i = 0; i < len; i++) {
        while (*d_i == 0)
            d_i++;

        data[i] = *d_i;
        (*d_i)--;
    }

    free(count);
    
    return 0;
}