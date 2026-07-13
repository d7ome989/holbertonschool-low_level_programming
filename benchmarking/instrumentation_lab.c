#include <stdio.h>
#include <time.h>

#define DATASET_SIZE 50000
#define SEED_VALUE 42u

static int dataset[DATASET_SIZE];

static unsigned int next_value(unsigned int *state)
{
    *state = (*state * 1103515245u) + 12345u;
    return *state;
}

static void build_dataset(void)
{
    unsigned int state;
    int i;

    state = SEED_VALUE;

    for (i = 0; i < DATASET_SIZE; i++)
        dataset[i] = (int)(next_value(&state) % 100000);
}

static void process_dataset(void)
{
    int i;
    int v;

    for (i = 0; i < DATASET_SIZE; i++)
    {
        v = dataset[i];
        v = (v * 3) + (v / 7) - (v % 11);
        if (v < 0)
            v = -v;
        dataset[i] = v;
    }
}

static unsigned long reduce_checksum(void)
{
    unsigned long sum;
    int i;

    sum = 0;
    for (i = 0; i < DATASET_SIZE; i++)
        sum = (sum * 131ul) + (unsigned long)dataset[i];

    return sum;
}

int main(void)
{
    unsigned long checksum;
    clock_t start;
    clock_t end;
    clock_t total_start;
    clock_t total_end;
    float total_sec;
    float build_data_sec;
    float process_sec;
    float reduce_sec;

    total_start = clock();

    start = clock();
    build_dataset();
    end = clock();
    build_data_sec = (float)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    process_dataset();
    end = clock();
    process_sec = (float)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    checksum = reduce_checksum();
    end = clock();
    reduce_sec = (float)(end - start) / CLOCKS_PER_SEC;

    total_end = clock();
    total_sec = (float)(total_end - total_start) / CLOCKS_PER_SEC;

    if (checksum == 0ul)
        printf("impossible\n");

    printf("TOTAL seconds: %.6f\n", total_sec);
    printf("BUILD_DATA seconds: %.6f\n", build_data_sec);
    printf("PROCESS seconds: %.6f\n", process_sec);
    printf("REDUCE seconds: %.6f\n", reduce_sec);

    return 0;
}
