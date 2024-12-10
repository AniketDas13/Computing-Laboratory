#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));
    int no_heads = 0, no_tails = 0;

    for (int i = 0; i < 100; i++)
    {
        if (rand() % 3 == 0) // simulates a biased coin with P(Chance of Head) = 1/3
        {
            cout << "Head" << endl;
            no_heads++;
        }
        else
        {
            cout << "Tail" << endl;
            no_tails++;
        }
    }

    cout << "Number of heads: " << no_heads << endl;
    cout << "Number of tails: " << no_tails << endl;

    return 0;
}