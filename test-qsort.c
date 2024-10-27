#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int roll_no;
    int marks;
};

int compare(const void *a, const void *b)
{
    const struct Student *pa = (const struct Student *)a;
    const struct Student *pb = (const struct Student *)b;
    return (pb->marks - pa->marks); // Sort in descending order of marks
}

int main()
{
    struct Student students[] = {{1, 85}, {2, 75}, {3, 90}, {4, 60}};
    int n = sizeof(students) / sizeof(students[0]);

    qsort(students, n, sizeof(students[0]), compare);

    /*
    void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

    base: A pointer to the first element of the array to be sorted.
    nmemb: The number of elements in the array.
    size: The size of each element in bytes.
    compar: A pointer to a comparison function that takes two pointers to elements and returns an integer:
    Negative: If the first element is less than the second.
    Zero: If the two elements are equal.
    Positive: If the first element is greater than the second.

    Eg: int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }
    ... qsort(arr, n, sizeof(int), compare); ...
    */

    printf("Students sorted by marks (descending order):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Roll No: %d, Marks: %d\n", students[i].roll_no, students[i].marks);
    }

    return 0;
}