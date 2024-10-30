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
    return (pa->roll_no - pb->roll_no); // Sort by roll number
}

int compare_marks(const void *a, const void *b)
{
    const struct Student *pa = (const struct Student *)a;
    const struct Student *pb = (const struct Student *)b;
    return (pb->marks - pa->marks); // Sort in descending order of marks
}

int compare(const void *a, const void *b)
{
    const struct Student *pa = (const struct Student *)a;
    const struct Student *pb = (const struct Student *)b;

    // Compare marks using double precision comparison
    if (pa->marks < pb->marks) // Sort by marks when in float or double
    {
        return -1;
    }
    else if (pa->marks > pb->marks)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    struct Student students[] = {{2, 85}, {4, 75}, {3, 90}, {1, 60}};
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

    // Sort the array by roll number
    printf("Students sorted by roll no. (ascending order):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Roll No: %d, Marks: %d\n", students[i].roll_no, students[i].marks);
    }

    // Search for a student with roll number 3
    int roll_no_to_find = 3;
    struct Student *found_student = bsearch(&roll_no_to_find, students, n, sizeof(students[0]), compare);

    // void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

    if (found_student)
    {
        printf("Student found: Roll No: %d, Marks: %d\n", found_student->roll_no, found_student->marks);
    }
    else
    {
        printf("Student not found.\n");
    }

    return 0;
}