#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Considering the sequence to be the first m natural numbers
void vitterReserviorAlgo(int m, int k, int reservoir[], int intervals[], int frequency[][101])
{
    for (int i = 0; i < k; i++) // initializes reservoir with first k elements
    {
        reservoir[i] = i + 1;
    }

    for (int i = k; i < m; i++) // processes remaining element & update reservior as per algorithm
    {
        int j = rand() % (i + 1);
        if (j < k)
        {
            reservoir[j] = i + 1;
        }

        for (int s = 0; s < 5; s++)
        {
            if (i + 1 == intervals[s])
            {
                for (int r = 0; r < k; r++)
                {
                    frequency[s][reservoir[r]]++;
                }
            }
        }
    }
}

int main()
{
    srand(time(0));
    int m = 100, k = 5;
    int runs = 1000;
    int reservoir[k];
    int intervals[5] = {20, 40, 60, 80, 100};
    int frequency[5][101] = {0};

    for (int r = 0; r < runs; r++)
    {
        vitterReserviorAlgo(m, k, reservoir, intervals, frequency);
    }

    for (int i = 0; i < 5; i++) // prints frequency of elements in the reservoir at m = 20, 40, 60, 80, 100
    {
        cout << "m = " << intervals[i] << endl;
        for (int j = 1; j <= m; j++)
        {
            if (frequency[i][j] > 0)
            {
                cout << j << ": " << frequency[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}