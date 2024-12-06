/* All times measured in minutes elapsed since 0500 */
#include "common.h"
#include "heap.h"

typedef struct
{
    int facility_id, duration;
} SERVICE;

typedef struct
{
    int arrival_time, total_service_time, waiting_time;
    int num_services, num_done;
    SERVICE *services;
} PATIENT;

typedef struct
{
    int patient_id, facility_id, timestamp, duration;
} EVENT;

/* Heap structure */
typedef struct
{
    unsigned int num_allocated, num_used;
    void *array;
    int element_size;
    int (*compare)(void *array, int i1, int i2);
} HEAP;

#if DEBUG == 1
static void print_data(PATIENT *patients, int num_patients, int num_facilities)
{
    int i, j;
    PATIENT *ptr;

    printf("%d %d\n", num_patients, num_facilities);
    for (i = 0, ptr = patients; i < num_patients; i++, ptr++)
    {
        printf("%04d %d ", ptr->arrival_time, ptr->num_services);
        for (j = 0; j < ptr->num_services; j++)
            printf("%d %d ", ptr->services[j].facility_id, ptr->services[j].duration);
        putchar('\n');
    }

    return;
}
#endif

static int hhmm_to_minutes(int arrival_time)
{
    return (arrival_time / 100 - 5) * 60 + arrival_time % 100;
}

static int minutes_to_hhmm(int minutes)
{
    return 100 * ((5 + minutes / 60) % 24) + minutes % 60;
}

static int compare_event_by_time(void *array, int i1, int i2)
{
    EVENT *p1 = (EVENT *)array + i1;
    EVENT *p2 = (EVENT *)array + i2;

    if (p1->timestamp == p2->timestamp)
        return p2->patient_id - p1->patient_id;
    return (p2->timestamp - p1->timestamp);
}

static void add_service_request_to_heap(HEAP *h, PATIENT *patients, int pid, int scheduled_time)
{
    PATIENT *ptr = patients + pid;
    EVENT e;

    if (ptr->num_done == ptr->num_services)
        return;
    e.patient_id = pid;
    e.facility_id = ptr->services[ptr->num_done].facility_id;
    e.timestamp = scheduled_time;
    e.duration = ptr->services[ptr->num_done].duration;
    insert(h, (void *)&e);
    ptr->num_done++;
    return;
}

int main(int ac, char *av[])
{
    int choice;
    int num_patients, num_facilities, i, j, s, t, d;
    int arrival_time, *next_available_at;
    PATIENT *patients, *ptr;
    EVENT current_event;
    HEAP h;

    if (ac != 2 ||
        (choice = atoi(av[1])) > 4 || choice < 1)
        ERR_MESG("Usage: hospital-scenario-simulator-with-heap <1 | 2 | 3 | 4>");

    scanf("%d %d", &num_patients, &num_facilities);
    if (NULL == (patients = Malloc(num_patients, PATIENT)) ||
        NULL == (next_available_at = (int *)calloc(num_facilities, sizeof(int))))
        ERR_MESG("hospital-scenario-simulator-with-heap: out of memory\n");

    /* Read input data */
    for (i = 0, ptr = patients; i < num_patients; i++, ptr++)
    {
        scanf("%d %d", &(arrival_time), &(ptr->num_services));
        ptr->arrival_time = hhmm_to_minutes(arrival_time);
        ptr->num_done = 0;
        ptr->total_service_time = 0;
        ptr->waiting_time = 0;
        if (NULL == (ptr->services = Malloc(ptr->num_services, SERVICE)))
            ERR_MESG("hospital-scenario-simulator-with-heap: out of memory\n");
        for (j = 0; j < ptr->num_services; j++)
        {
            scanf("%d %d", &(ptr->services[j].facility_id), &(ptr->services[j].duration));
            ptr->total_service_time += ptr->services[j].duration;
        }
    }
#if DEBUG == 1
    print_data(patients, num_patients, num_facilities);
#endif // DEBUG

    if (choice == 2)
    {
        for (i = 0; i < num_patients; i++)
            printf("%d %04d\n", i,
                   minutes_to_hhmm(patients[i].arrival_time + patients[i].total_service_time));
        return 0;
    }

    /* Build initial heap with first service of each patient */
    initHeap(&h, sizeof(EVENT), compare_event_by_time);
    for (i = 0; i < num_patients; i++)
        add_service_request_to_heap(&h, patients, i, patients[i].arrival_time);

    /* Delete event at root of heap; handle it; continue until heap is empty. */
    while (h.num_used > 0)
    {
        deleteMax(&h, (void *)&current_event);
        i = current_event.patient_id;
        j = current_event.facility_id;
        t = current_event.timestamp;
        d = current_event.duration;
        if (choice != 1 && t < next_available_at[j])
        {
            /* required facility is currently busy; current_event will have to wait */
            patients[i].waiting_time += next_available_at[j] - t;
            s = next_available_at[j];
            if (choice == 3)
                printf("%04d: Patient %d needs Facility %d for %d minutes, waits\n",
                       minutes_to_hhmm(t), i, j, d);
            // printf(" postponed to %04d\n", minutes_to_hhmm(t));
            current_event.timestamp = s;
            insert(&h, (void *)&current_event);
        }
        else
        { /* service current request */
            if (choice == 1 || choice == 3)
                printf("%04d: Facility %d attends to Patient %d for %d minutes\n",
                       minutes_to_hhmm(t), j, i, d);
            next_available_at[j] = current_event.timestamp + current_event.duration;
            add_service_request_to_heap(&h, patients, i, current_event.timestamp + current_event.duration);
        }
    }

    if (choice == 4)
        for (i = 0; i < num_patients; i++)
            printf("%d %d\n", i, patients[i].waiting_time);

    return 0;
}