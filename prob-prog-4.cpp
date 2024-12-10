#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void shuffleArray(int arr[], int n) // shuffles the array using rand()
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1); // uniformly generates an integer in the range [0, i]
        swap(arr[i], arr[j]);
    }
}

int main()
{
    srand(time(0));
    int numbers[100];

    for (int i = 0; i < 100; i++)
    {
        numbers[i] = i + 1;
    }

    shuffleArray(numbers, 100);

    for (int i = 0; i < 30; i++) // prints first 30 numbers from shuffled array
    {
        cout << numbers[i] << " ";
    }

    return 0;
}