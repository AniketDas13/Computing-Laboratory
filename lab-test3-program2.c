#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_HEAP_SIZE 20

typedef struct
{
    int arrival_min;
    int end_time;
    int services;
    int *facility;
    int *duration;
    int *curr_time;
    int waiting_time;
    char arrival_time[4];
} Patient;

typedef struct
{
    unsigned int num_allocated, num_used;
    int *array;
} INT_HEAP;

void initHeap(INT_HEAP *h)
{
    h->num_allocated = INIT_HEAP_SIZE;
    h->num_used = 0;
    if (NULL == (h->array = malloc(h->num_allocated * sizeof(int))))
    {
        perror("initHeap: out of memory");
        exit(-1);
    }
    return;
}

static void swapUpMin(INT_HEAP *h, int k)
{
    while (k > 1 && h->array[k / 2] > h->array[k])
    {
        int temp = h->array[k / 2];
        h->array[k / 2] = h->array[k];
        h->array[k] = temp;
        k /= 2;
    }
}

static void swapDownMin(INT_HEAP *h, int k)
{
    while (2 * k <= h->num_used)
    {
        int j = 2 * k;
        if (j < h->num_used && h->array[j] > h->array[j + 1])
        {
            j++;
        }
        if (h->array[k] <= h->array[j])
        {
            break;
        }
        int temp = h->array[k];
        h->array[k] = h->array[j];
        h->array[j] = temp;
        k = j;
    }
}

void insert(INT_HEAP *h, int x)
{
    if (h->num_used + 1 == h->num_allocated)
    {
        h->num_allocated *= 2;
        if (NULL == (h->array = realloc(h->array, h->num_allocated * sizeof(int))))
        {
            perror("insert: out of memory");
            exit(-1);
        }
    }

    h->num_used++;
    h->array[h->num_used] = x;
    swapUpMin(h, h->num_used);
}

int deleteMin(INT_HEAP *h)
{
    if (h->num_used == 0)
    {
        printf("Heap is empty\n");
        return -1;
    }

    int min = h->array[1];
    h->array[1] = h->array[h->num_used];
    h->num_used--;
    swapDownMin(h, 1);
    return min;
}

void buildHeapMin(INT_HEAP *h)
{
    for (int k = h->num_used / 2; k >= 1; k--)
    {
        swapDownMin(h, k);
    }
}

void heapsort(int *a, int N)
{
    INT_HEAP h;
    h.num_allocated = h.num_used = N;
    h.array = a;
    buildHeapMin(&h);

    while (h.num_used > 1)
    {
        int temp = h.array[1];
        h.array[1] = h.array[h.num_used];
        h.array[h.num_used] = temp;
        h.num_used--;
        swapDownMin(&h, 1);
    }
}

int hh_mm_to_minutes(char *time_str)
{
    int hours, minutes;
    if (sscanf(time_str, "%2d%2d", &hours, &minutes) != 2 || hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
    {
        return -1;
    }
    return hours * 60 + minutes;
}

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);

    INT_HEAP h;
    initHeap(&h);

    Patient *patient = (Patient *)malloc(m * sizeof(Patient));

    for (int i = 0; i < m; i++)
    {
        scanf("%s", patient[i].arrival_time);
        scanf("%d", &patient[i].services);

        patient[i].arrival_min = hh_mm_to_minutes(patient[i].arrival_time);

        patient[i].facility = (int *)malloc(patient[i].services * sizeof(int));
        patient[i].duration = (int *)malloc(patient[i].services * sizeof(int));
        patient[i].curr_time = (int *)malloc(patient[i].services * sizeof(int));

        patient[i].curr_time[0] = patient[i].arrival_min;
        for (int j = 0; j < patient[i].services; j++)
        {
            scanf("%d %d", &patient[i].facility[j], &patient[i].duration[j]);

            if (j == 0)
                continue;

            patient[i].curr_time[j] = patient[i].curr_time[j - 1] + patient[i].duration[j - 1];
        }

        patient[i].end_time = patient[i].curr_time[patient[i].services - 1] + patient[i].duration[patient[i].services - 1];
    }

    for (int i = 0; i < m; i++)
    {
        int time = patient[i].end_time;
        int hours = time / 60;
        int minutes = time % 60;
        if (hours > 23)
            hours -= 24;

        printf("%d %02d%02d\n", i, hours, minutes);
    }

    return 0;
}