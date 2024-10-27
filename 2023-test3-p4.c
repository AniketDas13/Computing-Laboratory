#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100

// Define the customer structure to hold arrival time, duration, and waiting time
typedef struct
{
    int cust_no;
    int arrival_minutes;      // Arrival time in minutes from start of the day
    int duration;             // Time required for the photocopy job in minutes
    int waiting_time;         // Calculated waiting time
    char arrival_time_str[6]; // Original arrival time as "HH:MM" string
} Customer;

// Part (a): Function to convert HH:MM format time string to minutes since the start of the day
int hh_mm_to_minutes(char *time_str)
{
    int hours, minutes;
    if (sscanf(time_str, "%2d:%2d", &hours, &minutes) != 2 || hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
    {
        return -1; // Return -1 for invalid time format
    }
    return hours * 60 + minutes;
}

// Helper function to read customer data
int read_customers(Customer customers[])
{
    int N, i;
    printf("Enter number of customers: ");
    if (scanf("%d", &N) != 1 || N < 1 || N > MAX_CUSTOMERS)
    {
        printf("Invalid number of customers.\n");
        return 0;
    }

    for (i = 0; i < N; i++)
    {
        customers[i].cust_no = i + 1;

        printf("Enter arrival time (HH:MM) and duration for customer %d: ", i + 1);
        scanf("%s %d", customers[i].arrival_time_str, &customers[i].duration);

        // Convert arrival time to minutes since the start of the day
        customers[i].arrival_minutes = hh_mm_to_minutes(customers[i].arrival_time_str);
        if (customers[i].arrival_minutes == -1)
        {
            printf("Invalid time format for customer %d.\n", i + 1);
            return 0;
        }
        customers[i].waiting_time = 0; // Initialize waiting time
    }

    return N;
}

// Part (b): Print customers in FCFS order based on arrival time
void print_fcfs_order(Customer customers[], int N)
{
    // Sort customers by arrival time in ascending order, maintaining the original order for ties
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (customers[i].arrival_minutes > customers[j].arrival_minutes)
            {
                // Swap customers to maintain FCFS order
                Customer temp = customers[i];
                customers[i] = customers[j];
                customers[j] = temp;
            }
        }
    }

    printf("\nFCFS Order of service based on arrival time:\n");
    for (int i = 0; i < N; i++)
    {
        printf("Customer %d: Arrival = %s, Duration = %d\n",
               customers[i].cust_no, customers[i].arrival_time_str, customers[i].duration);
    }
}

// Part (c): Calculate and print waiting times in descending order
void calculate_and_print_waiting_times(Customer customers[], int N)
{
    int current_time = 0;

    // Calculate waiting times for each customer
    for (int i = 0; i < N; i++)
    {
        // Waiting time is the difference between current_time and arrival time if current_time > arrival time
        if (current_time > customers[i].arrival_minutes)
        {
            customers[i].waiting_time = current_time - customers[i].arrival_minutes;
        }
        else
        {
            customers[i].waiting_time = 0;
            current_time = customers[i].arrival_minutes;
        }

        // Update current_time to the end of this customer's service
        current_time += customers[i].duration;
    }

    // Sort customers by waiting time in descending order
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (customers[i].waiting_time < customers[j].waiting_time)
            {
                Customer temp = customers[i];
                customers[i] = customers[j];
                customers[j] = temp;
            }
        }
    }

    // Print the customers along with their waiting times in descending order
    printf("\nCustomers and Waiting Times (Descending Order):\n");
    for (int i = 0; i < N; i++)
    {
        printf("Customer %d (Arrival: %s, Duration: %d, Waiting Time: %d mins)\n",
               customers[i].cust_no, customers[i].arrival_time_str, customers[i].duration, customers[i].waiting_time);
    }
}

int main()
{
    Customer customers[MAX_CUSTOMERS];
    int N;

    // Part (a): Read customers and validate time format
    N = read_customers(customers);
    if (N == 0)
        return 1; // Exit if customer data is invalid

    // Part (b): Print customers in FCFS order based on arrival time
    print_fcfs_order(customers, N);

    // Part (c): Calculate and print waiting times in descending order
    calculate_and_print_waiting_times(customers, N);

    return 0;
}