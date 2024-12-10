#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));
    double rand_no;
    int no_1 = 0, no_2 = 0, no_3 = 0, no_4 = 0;

    for (int i = 0; i < 100; i++)
    {
        rand_no = (double)rand() / RAND_MAX;
        // rand() uniformly generates an integer in the range [0, RAND_MAX]
        // rand() / RAND_MAX bounds this number in the range [0, 1)
        if (rand_no < 0.1)
        {
            cout << 1 << " ";
            no_1++;
        }
        else if (rand_no < 0.3)
        {
            cout << 2 << " ";
            no_2++;
        }
        else if (rand_no < 0.6)
        {
            cout << 3 << " ";
            no_3++;
        }
        else
        {
            cout << 4 << " ";
            no_4++;
        }
    }

    cout << "\nNumber of 1s in the sample: " << no_1;
    cout << "\nNumber of 2s in the sample: " << no_2;
    cout << "\nNumber of 3s in the sample: " << no_3;
    cout << "\nNumber of 4s in the sample: " << no_4;

    return 0;
}